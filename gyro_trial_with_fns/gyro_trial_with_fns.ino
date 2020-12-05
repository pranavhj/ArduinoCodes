

//GYRO INITIALIZATIONS

#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif


MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high




#define OUTPUT_READABLE_YAWPITCHROLL




#define LED_PIN 13                                                   // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

                                                                 // MPU control/status vars
bool dmpReady = false;                                                 // set true if DMP init was successful
uint8_t mpuIntStatus;                                              // holds actual interrupt status byte from MPU
uint8_t devStatus;                                                // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;                                                // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;                                               // count of all bytes currently in FIFO
uint8_t fifoBuffer[64];                                            // FIFO storage buffer

// orientation/motion vars
Quaternion q;                                                       // [w, x, y, z]         quaternion container
VectorInt16 aa;                                                // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;                                                 // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;                                               // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;                                              // [x, y, z]            gravity vector
float euler[3];                                                     // [psi, theta, phi]    Euler angle container
float ypr[3];                                                         // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

                                                                        // packet structure for InvenSense teapot demouint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

float yaw=0 , initial_yaw=0;



void setup() {
     #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24;                                                                       // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

                                                                                             // initialize serial communication
                                                                                           // (115200 chosen because it is required for Teapot Demo output, but it's
                                                                                             // really up to you depending on your project)
    Serial.begin(115200);
    while (!Serial); 
      mpu_initialize();                                                                                        // join I2C bus (I2Cdev library doesn't do this automatically)
   
while(1)
{initial_yaw=gyro_values();Serial.println(initial_yaw);


if(millis()>15500)
{break;}
}

}





void loop() {

    yaw=gyro_values()-initial_yaw;
    Serial.println(yaw);
}







void mpu_initialize()
{mpu.initialize();
devStatus = mpu.dmpInitialize();
 mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

if (devStatus == 0) {
                                                                                              // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

                                                                                                 // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

                                                                                                     // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

                                                                                                      // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);}







float gyro_values()
{while (!mpuInterrupt && fifoCount < packetSize) {
   }
 mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
 fifoCount = mpu.getFIFOCount();
 if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
                                                                                     // reset so we can continue cleanly
        mpu.resetFIFO();
        //Serial.println(F("FIFO overflow!"));
                                                                                       // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
                                                                              // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
               mpu.getFIFOBytes(fifoBuffer, packetSize);
                                                                     // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

       #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            /*Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);*/
        #endif

       
        return(ypr[0]*180/M_PI);
    }
    }

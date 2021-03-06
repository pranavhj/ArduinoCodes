
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

                                                                        // packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };




volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}



int motor_1_fw=23;
int motor_1_bw=22;         
int motor_2_fw=27;                  //motor intitialization
int motor_2_bw=26;


int motor_1_pwm=8;
int motor_2_pwm=9;
char s=0;int k=5;
float yaw_initial=0;
float yaw=0;



float kp_g=0.05, ki_g=0.00, kd_g=0;
float target_g=35.6;



float kp_g_r=0.5, ki_g_r=0, kd_g_r=0;
//float target_g=35.6;


void setup() {
                                                                                        // join I2C bus (I2Cdev library doesn't do this automatically)
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
    while (!Serial);                                                                       // wait for Leonardo enumeration, others continue immediately

                                                                                          // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
                                                                                           // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
                                                                                          // the baud timing being too misaligned with processor ticks. You must use
                                                                                          // 38400 or slower in these cases, or use some kind of external separate
                                                                                          // crystal solution for the UART timer.

                                                                                           // initialize device
                                                                                           //Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

                                                                                           // verify connection
    
    devStatus = mpu.dmpInitialize();

                                                                                          // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

                                                                                             // make sure it worked (returns 0 if so)
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
    pinMode(LED_PIN, OUTPUT);
    pinMode(motor_1_fw,OUTPUT);
    pinMode(motor_1_bw,OUTPUT);
    pinMode(motor_2_fw,OUTPUT);
    pinMode(motor_2_bw,OUTPUT);
    pinMode(motor_1_pwm,OUTPUT);
    pinMode(motor_2_pwm,OUTPUT);
    delay(15000);
}





void loop() {

    while (!mpuInterrupt && fifoCount < packetSize) {
       
    }

                                                                 // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

                                                                                   // get current FIFO count
    fifoCount = mpu.getFIFOCount();

                                                                                          // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
                                                                                     // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

                                                                                          // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
                                                                              // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

                                                                                     // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
                                                                                            // track FIFO count here in case there is > 1 packet available
                                                                        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

   

       #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            //Serial.print("ypr\t");
            //Serial.println(ypr[0] * 180/M_PI);                         //yaw
            //Serial.print("\t");
            //Serial.print(ypr[1] * 180/M_PI);
            //Serial.print("\t");
            //Serial.println(ypr[2] * 180/M_PI);
        #endif

        
    }

yaw=ypr[0] * 180/M_PI;
//Serial.println(yaw);






if(Serial.available()>0)
{ s=Serial.read();
}

if(s=='q')
{target_g=target_g-20;s='i';}

if(s=='r')
{target_g=target_g+20;s='i';}







 if(yaw!=target_g)
{ 
  int r=pid_func_gyro_rotation(target_g);
  Serial.print(yaw);Serial.print("       ");Serial.println(abs(r));
if(r>0)
{digitalWrite(motor_1_fw,1);
digitalWrite(motor_1_bw,0);
analogWrite(motor_1_pwm,250);

digitalWrite(motor_2_fw,1);
digitalWrite(motor_2_bw,0);
analogWrite(motor_2_pwm,250);
}
else
{ digitalWrite(motor_1_fw,0);
digitalWrite(motor_1_bw,1);
analogWrite(motor_1_pwm,250);

digitalWrite(motor_2_fw,0);
digitalWrite(motor_2_bw,1);
analogWrite(motor_2_pwm,250);
  }
}

/*else

{//Serial.println("4");
  digitalWrite(motor_1_fw,1);
digitalWrite(motor_1_bw,0);
analogWrite(motor_1_pwm,0);//Serial.print(pwmval_1);Serial.print("          ");

digitalWrite(motor_2_fw,0);
digitalWrite(motor_2_bw,1);
analogWrite(motor_2_pwm,0);//Serial.println(pwmval_2);
digitalWrite(13,LOW);
}
*/


   
}







int pid_func_gyro_rotation(int target_yaw)
{float currentvalue=yaw;
float error=currentvalue-target_yaw; static int lasterror=0;static float totalerror=0;
float pidterm=0;
   totalerror=totalerror+(error);totalerror=constrain(totalerror,-1700,1700);
    pidterm=kp_g_r*(error)+ki_g_r*(totalerror)+kd_g_r*(error-lasterror);
    lasterror=error;//Serial.println(pidterm);
return(constrain((pidterm),-180,180));
}

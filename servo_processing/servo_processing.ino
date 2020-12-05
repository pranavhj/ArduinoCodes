#include<Servo.h>

Servo myservo;                   // Create servo object to control a servo
int servoPin = 8;                // Connect yellow servo wire to digital I/O pin 4 
                     // Data received from the serial port

void setup() {
  myservo.attach(servoPin);      // Attach the servo to the PWM pin
  Serial.begin(9600);           // Start serial communication at 9600 bps
}

void loop() {
  
  for(int i=0;i<180;i=i+2)
 {myservo.write(i);delay(100);}
}

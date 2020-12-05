#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
int potpin1=0;
int potpin2=1;
int potpin3=2;
void setup() {
  // put your setup code here, to run once:
  pinMode(potpin1,INPUT);
  pinMode(potpin2,INPUT);
  pinMode(potpin3,INPUT);
   myservo1.attach(8);
   myservo2.attach(9);
   myservo3.attach(10);
   Serial.begin(9600);
   
  
}

void loop() {
  for(int i=0;i<180;i++)
  { myservo1.write(i);
 myservo2.write(i);
 myservo3.write(180-i);
 delay(20);

  }}


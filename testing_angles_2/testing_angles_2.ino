#include<Servo.h>                                                                           
Servo myservo1;
Servo myservo2;

Servo myservo3;

int switchpin=5;



int servo1[50]={81,92,95,91};



int servo2[50]={31,70,100,119};

int i=0;
int ledpin=13;

void setup() {
  // put your setup code here, to run once:
myservo2.attach(9);
myservo1.attach(8);myservo3.attach(10);
myservo3.write(54);
pinMode(switchpin,INPUT);pinMode(ledpin,OUTPUT);
Serial.begin(9600);servo1[0]=0;
servo2[0]=0;
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=0;i<=3;i++)
{if(servo1[i]-servo2[i]>0)
          {myservo1.write(servo1[i]);
          myservo2.write(servo1[i]-servo2[i]);delay(700);}

if( servo1[i]-servo2[i]<0)
         {myservo1.write(servo1[i]);
          myservo2.write(servo2[i]-servo1[i]);delay(700);}           
}}

#include<Servo.h>
Servo myservo;

int motorpinrightf=4;

int motorpinrightb=5;

int motorpinleftf=6;
int dsensor=9;
int motorpinleftb=7;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorpinrightf,OUTPUT);
  pinMode(motorpinrightb,OUTPUT);
   pinMode(motorpinleftf,OUTPUT);
  pinMode(motorpinleftb,OUTPUT);
  pinMode(dsensor,INPUT);
  myservo.attach(8);Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:



if(digitalRead(dsensor)==HIGH)
    {Serial.println(1);digitalWrite(motorpinrightb,HIGH);
digitalWrite(motorpinrightf,LOW);delay(1000);digitalWrite(motorpinleftb,LOW);
digitalWrite(motorpinleftf,LOW);

}else

{digitalWrite(motorpinrightb,HIGH);
digitalWrite(motorpinrightf,LOW);

digitalWrite(motorpinleftb,HIGH);
digitalWrite(motorpinleftf,LOW);

}}


#include<Servo.h>
Servo myservo;
int potpin=0;
int buttonclockwise=9;
int buttonanticlockwise=10;
int motorclockwise=11;
int motoranticlockwise=12;

void setup() {
  // put your setup code here, to run once:
pinMode(potpin,INPUT);
myservo.attach(8);
pinMode(buttonclockwise,INPUT);
pinMode(buttonanticlockwise,INPUT);
pinMode(motorclockwise,OUTPUT);
pinMode(motoranticlockwise,OUTPUT);
}

void loop() {





  
  // put your main code here, to run repeatedly:
int val=analogRead(potpin);
int potpinval=map(val,0,1023,0,180);
myservo.write(potpinval);



if(digitalRead(buttonclockwise==HIGH))
       {digitalWrite(motorclockwise,HIGH);
       digitalWrite(motoranticlockwise,LOW);delay(100);
       }
if(digitalRead(buttonanticlockwise==HIGH))
 {digitalWrite(motoranticlockwise,HIGH);
       digitalWrite(motorclockwise,LOW);delay(100);
       }

if(digitalRead(buttonanticlockwise==HIGH)    &&   digitalRead(buttonclockwise==HIGH))
      {digitalWrite(motorclockwise,LOW);
       digitalWrite(motoranticlockwise,LOW);}


if(digitalRead(buttonanticlockwise==LOW)    &&   digitalRead(buttonclockwise==LOW))
       {digitalWrite(motorclockwise,LOW);
       digitalWrite(motoranticlockwise,LOW);}


   


       


}

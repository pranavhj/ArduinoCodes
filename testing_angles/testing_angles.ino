#include<Servo.h>
Servo myservo1;
Servo myservo2;

Servo myservo3;

int switchpin=5;
int servo1[50];


int servo2[50];



int servo3[50];

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

void loop() {if(digitalRead(switchpin)==HIGH)   Serial.println("HIGH");
  // put your main code here, to run repeatedly:
while(i<100)
{if(Serial.available())
{int incomingvalue=Serial.read();
 if(i==0  ||  i%2==0)
    {servo1[i/2]=incomingvalue;
    }
  if(i!=0  &&  i%2!=0)
    {servo2[(i-1)/2]=incomingvalue;
    }



 delay(100);


  
  i++;
  
}}

if(i>=100)
 {digitalWrite(ledpin,HIGH);
 delay(200);
 digitalWrite(ledpin,LOW);
 delay(200);}


if(digitalRead(switchpin)==HIGH  )
   {for(i=0;i<=50;i++)
     {Serial.print(servo1[i]);
     Serial.print("       ");
     Serial.println(servo2[i]);
     }
   }}

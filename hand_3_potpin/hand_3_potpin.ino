#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
int potpin1=0;
int potpin2=1;
int potpin3=2;

int switchpin=11;
void setup() {
  // put your setup code here, to run once:
  pinMode(potpin1,INPUT);
  pinMode(potpin2,INPUT);
  pinMode(potpin3,INPUT);
   myservo1.attach(8);
   myservo2.attach(9);
   myservo3.attach(10);
   Serial.begin(9600);
  pinMode(switchpin,INPUT); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
int val1,val2,val3;
val1=analogRead(potpin1);
val1=map(val1,0,1023,0,180);                                                 //  46  102                     21  53          33 46      56  95
Serial.print(val1);Serial.print("    ");
val2=analogRead(potpin2);
val2=map(val2,0,1023,0,180);
Serial.print(val2);Serial.print("    ");
val3=analogRead(potpin3);
val3=map(val3,0,1023,0,180);
Serial.println(val3);                                                                                                       

   if(digitalRead(switchpin)==HIGH)
   {  Serial.println("on"); myservo3.write(6);} else  {  Serial.println("off"); myservo3.write(54);}            






                
  

 myservo1.write(val1);
 myservo2.write(val2);


delay(100);
}

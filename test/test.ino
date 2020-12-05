#include<Servo.h>
Servo myservo1;
Servo myservo2;int i=1;
Servo myservo3;
void setup() {
  // put your setup code here, to run once:
  
   myservo1.attach(8);
   myservo2.attach(9);
   myservo3.attach(10);
   Serial.begin(9600);}


   void loop()
  
  { 




   myservo1.write(0);
   myservo2.write(24);
 myservo3.write(125);
 delay(500);


 
 myservo1.write(37);
 myservo2.write(39);
 myservo3.write(131);
delay(500);



 
 myservo1.write(43);
 myservo2.write(27);
 myservo3.write(131);
delay(500);


 myservo1.write(21);
 myservo2.write(0);
 myservo3.write(131);
delay(500);


 
 


 
   }


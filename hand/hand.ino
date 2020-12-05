int potpin1=1;
int potpin2=2;
int potpin3=3;
#include<Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;




void setup() {
  // put your setup code here, to run once:
servo1.attach(8);
servo2.attach(9);
servo3.attach(10);
pinMode(potpin1,INPUT);
pinMode(potpin2,INPUT);
pinMode(potpin3,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int val1,val2,val3;
  val1=analogRead(potpin1);
  val2=analogRead(potpin2);
  val3=analogRead(potpin3);


  val1=map(val1,0,1023,0,180);
  val2=map(val2,0,1023,0,180);
  val3=map(val3,0,1023,0,180);
Serial.print(val1);Serial.print("   ");Serial.print(val2);Serial.print("   ");Serial.println(val3);

  servo1.write(val1);
  servo2.write(val2);
  servo3.write(val3);
delay(100);
}

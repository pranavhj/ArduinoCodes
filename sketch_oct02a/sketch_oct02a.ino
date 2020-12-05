#include <Servo.h>

Servo esc1;
Servo esc3;


void setup() {
 
  Serial.begin(9600);
 
  
  esc1.attach(6);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc1.write(30);
  delay(1000);
 

}

void loop() {
  
  esc1.write(180);
  
}


#include<Servo.h>
#include <IRremote.h>
int ledpin=9;int counter=0;

int IR_Recv = 8;   //IR Receiver Pin 3

IRrecv irrecv(IR_Recv);
decode_results results;

Servo myservo;
void setup(){
  Serial.begin(9600);  //starts serial communication
  irrecv.enableIRIn(); // Starts the receiver
  pinMode(ledpin,OUTPUT);
  myservo.attach(7);
}
void loop(){
  //decodes the infrared input
  if (irrecv.decode(&results)){
    long int decCode = results.value;
    Serial.print(decCode);
    if(results.value==284117430)
     {counter=counter+30;}
    if(results.value==284105700)
    {counter=counter-30;}
     





myservo.write(counter);

Serial.print("  ");Serial.println(counter);
     irrecv.resume();
  }

}

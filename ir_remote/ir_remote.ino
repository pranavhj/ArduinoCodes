#include <IRremote.h>
int ledpin=9;

int IR_Recv = 8;   //IR Receiver Pin 3

IRrecv irrecv(IR_Recv);
decode_results results;


void setup(){
  Serial.begin(9600);  //starts serial communication
  irrecv.enableIRIn(); // Starts the receiver
  pinMode(ledpin,OUTPUT);
}
void loop(){
  //decodes the infrared input
  if (irrecv.decode(&results)){
     long int decCode = results.value;
    Serial.println(decCode);
    if(results.value==1079865487)

   { digitalWrite(ledpin,HIGH);

}
     if(results.value==1079857327)
 {digitalWrite(ledpin,LOW);
     
  }
    
 if(results.value==1079861407)
 {for(int i=0;i<100;i++)
 {digitalWrite(ledpin,HIGH);
  delay(100);
  digitalWrite(ledpin,LOW);
    delay(100);}
 }
  

  
   
    
    
    irrecv.resume();
  }
    
  }

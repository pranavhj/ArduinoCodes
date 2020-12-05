
#include <IRremote.h>
int motoropen=11;
int motorclose=10;
int button=9;
boolean state=HIGH;
char bstate=0;
int ledpin=13;


int IR_Recv = 8;   //IR Receiver Pin 3

IRrecv irrecv(IR_Recv);
decode_results results;
void setup() {
  // put your setup code here, to run once:
pinMode(motoropen,OUTPUT);
pinMode(motorclose,OUTPUT);
pinMode(button,INPUT);
pinMode(ledpin,OUTPUT);
Serial.begin(9600);
int l=9;
while(l>5)
{
  if(digitalRead(button)==HIGH)
  {delay(100);
digitalWrite(motoropen,HIGH);
digitalWrite(motorclose,LOW);
delay(170);
break;
Serial.println(9);




  }
}
irrecv.enableIRIn(); // Starts the receiver
  pinMode(ledpin,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(motoropen,LOW);
digitalWrite(motorclose,LOW);
digitalWrite(ledpin,LOW);


if(digitalRead(button)==HIGH  &&  state==LOW)
{//Serial.println(digitalRead(button));
  delay(100);
  digitalWrite(motoropen,HIGH);
digitalWrite(motorclose,LOW);
delay(170);
state=HIGH;
}
if(digitalRead(button)==HIGH  &&  state==HIGH)
{//Serial.println(digitalRead(button));
  delay(100);
  digitalWrite(motoropen,LOW);
digitalWrite(motorclose,HIGH);
delay(170);
state=LOW;}


if(Serial.available()>0)
{ bstate=Serial.read();
{if(state==1)
{Serial.println("Its Closed");}
if(state==0)
{Serial.println("Its Open");}
}

delay(20);
}



if(bstate=='q'  &&  state==LOW)
{delay(100);
  digitalWrite(motoropen,HIGH);
digitalWrite(motorclose,LOW);

delay(170);
state=HIGH;
bstate=0;

}


if(bstate=='q'  &&  state==HIGH)
{delay(100);
  digitalWrite(motoropen,LOW);
digitalWrite(motorclose,HIGH);
delay(170);
state=LOW;
bstate=0;}



if (irrecv.decode(&results)){
     long int decCode = results.value;
    //Serial.println(decCode);
     {if(state==1)
{Serial.println("Its Closed");}
if(state==0)
{Serial.println("Its Open");}
}



    if((decCode==351002655    )  &&  state==LOW)                  // 284154150 
{delay(100);
  digitalWrite(motoropen,HIGH);
digitalWrite(motorclose,LOW);

delay(170);
state=HIGH;
decCode=0;
}


if(decCode==351002655   &&  state==HIGH)
{delay(100);
  digitalWrite(motoropen,LOW);
digitalWrite(motorclose,HIGH);
delay(170);
state=LOW;
decCode=0;}


 if((decCode==284154150    )  &&  state==LOW)                  // 284154150 
{delay(100);
  digitalWrite(motoropen,HIGH);
digitalWrite(motorclose,LOW);

delay(170);
state=HIGH;
decCode=0;
}


if(decCode==284154150    &&  state==HIGH)
{delay(100);
  digitalWrite(motoropen,LOW);
digitalWrite(motorclose,HIGH);
delay(170);
state=LOW;
decCode=0;}

irrecv.resume();
}   
}

int motoropen=11;
int motorclose=10;
int button=9;
boolean state=HIGH;
char bstate=0;
int ledpin=13;
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
delay(130);
break;
Serial.println(9);




  }
}
}
void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(motoropen,LOW);
digitalWrite(motorclose,LOW);
digitalWrite(ledpin,LOW);


if(digitalRead(button)==HIGH  &&  state==LOW)
{Serial.println(digitalRead(button));
  delay(100);
  digitalWrite(motoropen,HIGH);
digitalWrite(motorclose,LOW);
delay(130);
state=HIGH;
}
if(digitalRead(button)==HIGH  &&  state==HIGH)
{Serial.println(digitalRead(button));
  delay(100);
  digitalWrite(motoropen,LOW);
digitalWrite(motorclose,HIGH);
delay(130);
state=LOW;}


if(Serial.available()>0)
{ bstate=Serial.read();
Serial.println(bstate);

delay(20);
}



if(bstate=='q'  &&  state==LOW)
{delay(100);
  digitalWrite(motoropen,HIGH);
digitalWrite(motorclose,LOW);

delay(130);
state=HIGH;
bstate=0;
}


if(bstate=='q'  &&  state==HIGH)
{delay(100);
  digitalWrite(motoropen,LOW);
digitalWrite(motorclose,HIGH);
delay(130);
state=LOW;
bstate=0;}
}

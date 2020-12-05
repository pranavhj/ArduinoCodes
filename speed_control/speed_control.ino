int motorleft=7;
int motorright=8;
int motorspeed=9;int potpin=0;
boolean a=HIGH,LOW;

void setup() {
  // put your setup code here, to run once:
pinMode(motorleft,OUTPUT);
pinMode(motorspeed,OUTPUT);
pinMode(motorright,OUTPUT);
pinMode(potpin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int x=analogRead(potpin);int var=map(x,0,1023,0,255);
digitalWrite(motorleft,a);
digitalWrite(motorright,b);
analogWrite(motorspeed,255);
delay(8000);


digitalWrite(motorleft,LOW);
digitalWrite(motorright,HIGH);
analogWrite(motorspeed,255);


}

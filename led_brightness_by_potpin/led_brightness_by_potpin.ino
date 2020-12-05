int potpin=1;
int ledpin=3;


void setup() {
  // put your setup code here, to run once:
pinMode(potpin,INPUT);
pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int val=analogRead(potpin);
val=val/4;
analogWrite(ledpin,val);
}

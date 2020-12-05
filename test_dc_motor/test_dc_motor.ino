int i1=46 ,i2=47,ea=7;
int i3=50 ,i4=51,ea1=9;

void setup() {
  // put your setup code here, to run once:
pinMode(i1,OUTPUT);
pinMode(i2,OUTPUT);
pinMode(ea,OUTPUT);

pinMode(i3,OUTPUT);
pinMode(i4,OUTPUT);
pinMode(ea1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(i1,HIGH);
digitalWrite(i2,LOW);
analogWrite(ea,255);


digitalWrite(i3,HIGH);
digitalWrite(i4,LOW);
analogWrite(ea1,255);

}

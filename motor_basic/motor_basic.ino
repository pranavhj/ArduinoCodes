 int p=30,c=32,a=5;                       //          26  28  4    motor2 or 0        30  22  5

void setup() {
  // put your setup code here, to run once:
pinMode(p,OUTPUT);

pinMode(c,OUTPUT);

pinMode(a,OUTPUT);
Serial.begin(9600);
Serial.println("start");
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(c,HIGH);
 digitalWrite(p,LOW);
 analogWrite(a,255);

delay(1500);

//digitalWrite(p,HIGH);
 //digitalWrite(c,LOW);
 //analogWrite(a,255);

delay(1500);



}

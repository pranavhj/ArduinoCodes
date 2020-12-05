void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(7,INPUT);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int i=digitalRead(7);
Serial.println(i);
digitalWrite(13,HIGH);

}

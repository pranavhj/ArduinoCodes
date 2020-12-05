int enc1=4;
int enc2=5;
void setup() {
  // put your setup code here, to run once:
pinMode(enc1,INPUT);
pinMode(enc2,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(analogRead(0));Serial.print("        ");Serial.println(analogRead(1));
}

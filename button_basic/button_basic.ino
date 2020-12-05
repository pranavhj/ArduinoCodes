int switchpin=10;

void setup() {
  // put your setup code here, to run once:
pinMode(switchpin,INPUT);Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(switchpin)==HIGH)   Serial.println("HIGH");

else  Serial.println("LOW");

delay(200);
}

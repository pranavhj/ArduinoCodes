int ldrpin=0;
int ledpin=9;


void setup() {
  // put your setup code here, to run once:
pinMode(ldrpin,INPUT);pinMode(ledpin,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int val=analogRead(ldrpin);
Serial.println(val);
analogWrite(ledpin,10);

}

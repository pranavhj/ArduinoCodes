int ledpin=9;


void setup() {pinMode(ledpin,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(ledpin,10);delay(500);

}

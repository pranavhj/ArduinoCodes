#include <IRremote.h>

#define PIN_IR 3
#define PIN_DETECT 8
#define PIN_LED 13

IRsend irsend;
void setup()
{
  pinMode(PIN_DETECT, INPUT);
  pinMode(PIN_LED, OUTPUT);
  irsend.enableIROut(38);
  irsend.mark(0);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  Serial.println(digitalRead(PIN_DETECT));
}

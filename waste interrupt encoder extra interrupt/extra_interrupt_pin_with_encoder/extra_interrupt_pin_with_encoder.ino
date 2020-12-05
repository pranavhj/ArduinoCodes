#define encoder0PinA  0
#define encoder0PinB  9

volatile int encoder0Pos = 0; 





void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
 
// Use one Routine to handle each group
 
ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
 {    
     digitalWrite(13,digitalRead(8) and digitalRead(9));
 }
 
ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
 {
     digitalWrite(13,digitalRead(A0));
 }  
 
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
 {
     digitalWrite(13,digitalRead(7));
 } 





void setup()
   {int i;
 
// set pullups, if necessary
  for (i=0; i<=12; i++)
      digitalWrite(i,HIGH);  // pinMode( ,INPUT) is default
 
  for (i=A0; i<=A5; i++)
      digitalWrite(i,HIGH);
 
  pinMode(13,OUTPUT);  // LED
 
// enable interrupt for pin...
 
  pciSetup(A0);
 
   pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pull-up resistor
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pull-up resistor

  attachInterrupt(digitalPinToInterrupt(A0), doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
  Serial.begin (9600);
  
   }



void loop()
{}





void doEncoder() {
  /* If pinA and pinB are both high or both low, it is spinning
   * forward. If they're different, it's going backward.
   *
   * For more information on speeding up this process, see
   * [Reference/PortManipulation], specifically the PIND register.
   */
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;delay(20);
  } else {
    encoder0Pos--;delay(20);
  }

  Serial.println (encoder0Pos, DEC);
}
  

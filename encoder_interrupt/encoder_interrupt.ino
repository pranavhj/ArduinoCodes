  #define encoder0PinA  2
#define encoder0PinB  22


volatile int encoder0Pos = 0;
int motorclockwise=7;
int motoranticlockwise=8;
int motorpwm=9;


double prev_time=0;
double time_1=0;

void setup() {
  pinMode(motorclockwise,OUTPUT);
pinMode(motoranticlockwise,OUTPUT);
pinMode(motorpwm,OUTPUT); 


  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, LOW);       // turn on pull-up resistor
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, LOW);       // turn on pull-up resistor

  attachInterrupt(digitalPinToInterrupt(2), doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk

} 

void loop(){


//digitalWrite(7,1);
//digitalWrite(8,0);
//analogWrite(9,255);



//delay(1000);


//digitalWrite(7,1);
//digitalWrite(8,0);
//analogWrite(9,255);
//delay(1000);

// do some stuff here - the joy of interrupts is that they take care of themselves
}

void doEncoder() {
  /* If pinA and pinB are both high or both low, it is spinning
   * forward. If they're different, it's going backward.
   *
   * For more information on speeding up this process, see
   * [Reference/PortManipulation], specifically the PIND register.
   */
   time_1=millis();
   if(abs(time_1-prev_time)>50)
  {if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }

  Serial.println (encoder0Pos);
  prev_time=millis();
  }

  
}

/* See this expanded function to get a better understanding of the
 * meanings of the four possible (pinA, pinB) value pairs:
 */
void doEncoder_Expanded(){
  if (digitalRead(encoder0PinA) == HIGH) {   // found a low-to-high on channel A
    if (digitalRead(encoder0PinB) == LOW) {  // check channel B to see which way
                                             // encoder is turning
      encoder0Pos = encoder0Pos - 1;       // CCW
    } 
    else {
      encoder0Pos = encoder0Pos + 1;        // CW
    }
  }
  else                                        // found a high-to-low on channel A
  { 
    if (digitalRead(encoder0PinB) == LOW) {   // check channel B to see which way
                                              // encoder is turning  
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;        // CCW
    }

  }
  Serial.println (encoder0Pos, DEC);          // debug - remember to comment out
                                              // before final program run
  // you don't want serial slowing down your program if not needed
}

/*  to read the other two transitions - just use another attachInterrupt()
in the setup and duplicate the doEncoder function into say, 
doEncoderA and doEncoderB. 
You also need to move the other encoder wire over to pin 3 (interrupt 1). 
*/ 

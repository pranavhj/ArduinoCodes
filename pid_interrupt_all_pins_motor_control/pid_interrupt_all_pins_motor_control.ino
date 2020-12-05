#include"PinChangeInterrupt.h"
#define encoder0PinA  8

#define encoder0PinB  9

volatile int encoder0Pos = 0;
float kp=0,ki=0,kd=0;
int motorclockwise=7;
int motoranticlockwise=11;
int motorpwm=12;
boolean a=LOW,b=LOW;int pwmv=0;int target=500;
void setup() { 

  pinMode(motorclockwise,OUTPUT);
  pinMode(motoranticlockwise,OUTPUT);
  pinMode(motorpwm,OUTPUT);
  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pull-up resistor
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pull-up resistor

  attachPCINT(digitalPinToPCINT(encoder0PinA), doEncoder_Expanded, CHANGE);  // encoder pin on interrupt 0 - pin 2
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk
  
} 

void loop(){ 
  // put your main code here, to run repeatedly:
disablePCINT(digitalPinToPCINT(encoder0PinA));
int pwmval=pidfunc(encoder0Pos,target,pwmv);
enablePCINT(digitalPinToPCINT(encoder0PinA));
   digitalWrite(7,a);
   digitalWrite(8,b);
   analogWrite(9,pwmval);

  
}

int pidfunc(int currentvalue,int targetvalue,int pwmvalue)
 
   {
    int error=targetvalue-currentvalue;static int lasterror=0;static int totalerror=0;
    float pidterm=0;
    totalerror=totalerror+error;
    pidterm=kp*(error)+ki*(totalerror)+kd*(error-lasterror);
    lasterror=error;
    return(constrain((int(pidterm)+pwmvalue),0,255));
    if(error>0)
    {a=HIGH;b=LOW;}
    else
    {a=LOW;b=HIGH;}
    
   }

void doEncoder() {
  /* If pinA and pinB are both high or both low, it is spinning
   * forward. If they're different, it's going backward.
   *
   * For more information on speeding up this process, see
   * [Reference/PortManipulation], specifically the PIND register.
   */
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }

  Serial.println (encoder0Pos, DEC);
}

/* See this expanded function to get a better understanding of the
 * meanings of the four possible (pinA, pinB) value pairs:
 */
void doEncoder_Expanded(){
  if (digitalRead(encoder0PinA) == HIGH) {   // found a low-to-high on channel A
    if (digitalRead(encoder0PinB) == LOW) {  // check channel B to see which way
                                             // encoder is turning
      encoder0Pos = encoder0Pos - 1;delay(20);        // CCW
    } 
    else {
      encoder0Pos = encoder0Pos + 1;delay(20);         // CW
    }
  }
  else                                        // found a high-to-low on channel A
  { 
    if (digitalRead(encoder0PinB) == LOW) {   // check channel B to see which way
                                              // encoder is turning  
      encoder0Pos = encoder0Pos + 1;delay(20);          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;delay(20);          // CCW
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

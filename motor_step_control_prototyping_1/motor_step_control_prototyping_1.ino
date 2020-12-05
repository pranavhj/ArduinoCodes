

float kp=40 ,ki=0,kd=10;
int motorclockwise=7;
int motoranticlockwise=8;
int motorpwm=9;
int encoder0PinA=2;
int encoder0PinB=8;int ledpin=13;
volatile int encoder0Pos=0;boolean a=LOW,b=LOW;int pwmval=0;int i=0;int target=300;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin,OUTPUT);
pinMode(motorclockwise,OUTPUT);
pinMode(motoranticlockwise,OUTPUT);
pinMode(motorpwm,OUTPUT);
pinMode(encoder0PinA,INPUT);digitalWrite(encoder0PinA, HIGH);
pinMode(encoder0PinB,INPUT);digitalWrite(encoder0PinB, HIGH);
attachInterrupt(digitalPinToInterrupt(2),encoderReading, CHANGE);

Serial.begin(9600);
Serial.println("start"); 
}


void loop() {
  // put your main code here, to run repeatedly:
 runmotor(3);


}

int runmotor(int t)
  { int t1=t;
  while(t1-t!=0)
    {pwmval=pidfunc(encoder0Pos,t,pwmval);
    
    digitalWrite(7,a);if(a==HIGH){digitalWrite(13,HIGH);}   else   {digitalWrite(13,LOW);}
   digitalWrite(8,b);
   
   analogWrite(9,pwmval);
   t1=t-encoder0Pos;
     if( (  ((t-encoder0Pos)<2) || ((t-encoder0Pos)>-2) )  &&  pwmval<40)
   break;
  
   
   }}
int pidfunc(int currentvalue,int targetvalue,int pwmvalue)
 
   {
    int error=targetvalue-currentvalue;static int lasterror=0;static int totalerror=0;
    float pidterm=0;
     if(error>0)
    {a=HIGH;b=LOW;}
    else
    {a=LOW;b=HIGH;}
   
    
    totalerror=totalerror+error;
    pidterm=kp*(error)+ki*(totalerror)+kd*(error-lasterror);
    lasterror=error;
   
    return(constrain(abs(pwmvalue+pidterm),0,255));
   
   }
void encoderReading()
{ /* If pinA and pinB are both high or both low, it is spinning
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

  Serial.println (encoder0Pos);
}

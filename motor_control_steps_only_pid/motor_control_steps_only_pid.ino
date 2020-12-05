

float kp=40 ,ki=0.002,kd=10;
int motorclockwise=7;
int motoranticlockwise=8;
int motorpwm=9;
int encoder0PinA=2;
int encoder0PinB=3;int ledpin=13;
volatile int encoder0Pos=0;boolean a=LOW,b=LOW;int pwmval=0;int i=0;
int n=0;int counter=0;
void encoderReading();
int pidfunc(int,int,int);
 
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
runmotor(100);

}

int runmotor(int t)
  { int t1=t;
  while((t1-encoder0Pos)!=0)
    {pwmval=pidfunc(encoder0Pos,t,pwmval);
    //Serial.print(pwmval);Serial.print("                 ");Serial.println(encoder0Pos);Serial.print("                 ");Serial.println(a);
       digitalWrite(7,a);
       digitalWrite(8,b);
       analogWrite(9,pwmval);
   t1=t-encoder0Pos;
   if( (  ((t-encoder0Pos)<2) || ((t-encoder0Pos)>-2) )  &&  pwmval<40)
   break;}
    if((t-encoder0Pos)==0)
   {pwmval=pidfunc(2000,2000,2000);counter++;}
   
   }
int pidfunc(int currentvalue,int targetvalue,int pwmvalue)

 {
   pwmvalue=0;
    int error=targetvalue-currentvalue;static int lasterror=0;static int totalerror=0;
    float pidterm=0;
    if(currentvalue==targetvalue && targetvalue==pwmvalue)
      { lasterror=0;totalerror=0;}
    
     
     if(error>0)
    {a=HIGH;b=LOW;}
    else
    {a=LOW;b=HIGH;}
   
    
    totalerror=totalerror+error;
    pidterm=kp*(error)+ki*(totalerror)+kd*(error-lasterror);
    lasterror=error;pidterm=abs(pidterm);
    //Serial.println(pidterm);
   
    return(constrain((pwmvalue+pidterm),0,255));
   
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


int callpos()
{return(4000);
 }


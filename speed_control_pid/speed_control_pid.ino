float kp=0.5,ki=0.0 ,kd=0.1;
int motorclockwise=7;
int motoranticlockwise=8;
int motorpwm=9;
int encoder0PinA=2;
int encoder0PinB=3;int ledpin=13;
volatile float encoder0Pos=0;int oldPos=0;int newPos=0;int oldTime=0;int newTime=0;float target=7;int pwmv=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin,OUTPUT);
pinMode(motorclockwise,OUTPUT);
pinMode(motoranticlockwise,OUTPUT);
pinMode(motorpwm,OUTPUT);
pinMode(encoder0PinA,INPUT);digitalWrite(encoder0PinA, HIGH);
pinMode(encoder0PinB,INPUT);digitalWrite(encoder0PinB, HIGH);
attachInterrupt(digitalPinToInterrupt(2),doEncoder, CHANGE);

Serial.begin(9600);
Serial.println("start"); 
digitalWrite(7,1);
digitalWrite(8,0);
analogWrite(9,255);


}



void doEncoder()
{ /* If pinA and pinB are both high or both low, it is spinning
   * forward. If they're different, it's going backward.
   *
   * For more information on kl speeding up this process, see
   * [Reference/PortManipulation], specifically the PIND register.
   */
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }

  //Serial.println (encoder0Pos);
}
float speedmeasurement()
   {int timeold=millis();int timenew=timeold;int initial=encoder0Pos;int final;
    while(timenew<(timeold+1000))
      {final=encoder0Pos;
       timenew=millis();}
     float disp;
     disp=(final-initial);
     
     return(disp);}
    




void loop() {
  delay(1000);
float current=(speedmeasurement())*3;Serial.println(current);
pwmv=pidfunc(155,current,pwmv);//Serial.println(pwmv);//Serial.print("                  ");Serial.println(current);
{digitalWrite(7,1);digitalWrite(8,0);analogWrite(9,pwmv);}


//{digitalWrite(7,0);digitalWrite(8,1);analogWrite(9,255);}



 
}




int pidfunc(float targetValue,float currentValue,int pwmvalue)
   {float error=targetValue-currentValue;
   static float lastError=0,totalError=0;
   totalError=totalError+error;//Serial.print("err");Serial.println(totalError);
   //if(totalError>5){totalError=0;}
   float pidterm=kp*(error)+ki*(totalError)+kd*(error-lastError);
   lastError=error;
   return(constrain(abs(pwmvalue+pidterm),0,255));
   }

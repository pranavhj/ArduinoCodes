int motorclockwise=7;
int motoranticlockwise=8;
int motorpwm=9;
int encoder0PinA=2;
int encoder0PinB=3;int ledpin=13;
volatile float encoder0Pos=0;int oldPos=0;int newPos=0;int oldTime=0;int newTime=0;int target=300;int pwmv=0;

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
digitalWrite(7,0);
digitalWrite(8,1);
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
     float vel;
     vel=(final-initial);//Serial.println(final-initial);
     
     return(vel);}
    




void loop() {
  delay(1000);

 newPos=encoder0Pos;
 newTime=millis();
 float speed=0;
 //speed=1000/30*(newPos-oldPos)/(newTime-oldTime);

    
 speed=speedmeasurement();
 Serial.println(speed);
 oldPos=newPos;
 oldTime=newTime;


 
}






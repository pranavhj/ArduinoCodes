
int IN1=8;//connected to Arduino's port 3
int IN2=9;//connected to Arduino's port 4

int IN3=10;//connected to Arduino's port 6
int IN4=11;//connected to Arduino's port 7
 int stepcount=0;
void setup()
{Serial.begin(9600);
 
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 
}
void stepclockwise(int steps,int wait)
  {
    for(int i=steps;i>=0;i--)
     {digitalWrite(IN1,LOW);
     digitalWrite(IN2,HIGH);
     digitalWrite(IN3,HIGH);
     digitalWrite(IN4,LOW);
     delay(wait);
     digitalWrite(IN1,LOW);
     digitalWrite(IN2,HIGH);
     digitalWrite(IN3,LOW);
     digitalWrite(IN4,HIGH);
     delay(wait);
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     digitalWrite(IN3,LOW);
     digitalWrite(IN4,HIGH);
     delay(wait);stepcount++;
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     digitalWrite(IN3,HIGH);
     digitalWrite(IN4,LOW);
     delay(wait);}
 }



 void stepanticlockwise(int steps,int wait)
  { for(int i=steps;i>=0;i--)
     {digitalWrite(IN1,LOW);
     digitalWrite(IN2,HIGH);
     digitalWrite(IN4,HIGH);
     digitalWrite(IN3,LOW);
     delay(wait);
     digitalWrite(IN1,LOW);
     digitalWrite(IN2,HIGH);
     digitalWrite(IN4,LOW);
     digitalWrite(IN3,HIGH);
     delay(wait);
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     digitalWrite(IN4,LOW);
     digitalWrite(IN3,HIGH);
     delay(wait);stepcount++;
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     digitalWrite(IN4,HIGH);
     digitalWrite(IN3,LOW);
     delay(wait);}
    
 }
 
void loop()
{/*In the way of 4 beats to drive the stepping motor,A group connected to motorA,B
 B group connected to motorB,Suppose A representing the forward current of A group,
 A- representing the reverse current of A group,B representing the forward current of B group,
 B- representing the reverse current of B group.
 this way run as follow:
 AB    A-B    A-B-   AB-
 or
 AB   AB-    A-B-   A-B
*/
if(stepcount==0)
{
  stepclockwise(96,1);
 delay(100);
  stepanticlockwise(264,2);stepcount++;}
}

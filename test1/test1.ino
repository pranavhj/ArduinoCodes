
int pwm1=11;


int pwm2=10;


void setup() {
  // put your setup code here, to run once:

pinMode(pwm1,INPUT);
pinMode(pwm2,INPUT);



for(int i=254;i>0;i=i-10)
{
 analogWrite(pwm1,i);



 analogWrite(pwm2,i);delay(50);}
 
}

void loop() {
  // put your main code here, to run repeatedly:

/*for(int i=0;i<255;i=i+10)
{
 analogWrite(pwm1,i);



 analogWrite(pwm2,i);delay(500);}

// delay(500);


 for(int i=255;i>0;i=i-10)
{
 analogWrite(pwm1,i);



 analogWrite(pwm2,i);

delay(500);
}
 */

 //analogWrite(pwm1,0);



 //analogWrite(pwm2,0);

 



  
}

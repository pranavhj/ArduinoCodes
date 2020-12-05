int pwm_pin=0;
int pwm=0;
void setup() {
  // put your setup code here, to run once:
pinMode(pwm_pin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0)
{
  char r=Serial.read();
  if(r=='s')
  {pwm=pwm+5;}
  if(r=='r')
  {pwm=pwm-5;}

}
}
analogWrite(pwm_pin,pwm)

}

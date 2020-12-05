#include<Servo.h>
int ldr[4]={12,13,14,15},ledpin[4]={2,3,4,5},sum=0,fum=0,d[8]={-40,-30,-20,-10,10,20,30,40},count=0,value[100],avg[4],temp,h,z[4];
Servo myservo;
float dir,meandir;
void setup() 
{
  myservo.attach(1);
  for(int i=0;i<4;i++)
  {
    pinMode(ldr[i],INPUT);
  }
  for(int i=0;i<4;i++)
  {
    pinMode(ledpin[i],OUTPUT);
  }

}

void calib()
{
  int i;
  for(int x=0;x<4;i++)
  {
  for(i=0;i<100;i++)
  {
    value[i]=analogRead(ldr[x]);
    delay(10);
  }
  for(int i=0;i<100;i++)
  {
   for(int j=0;j<99;j++)
  {
    if(value[j]<value[j+1])
    {
      temp=value[j];
      value[j]=value[j+1];
      value[j+1]=temp;
    }
  }
  }
  avg[x]=(value[0]+value[99])/2;
  }
}

void loop() 
{
  for(int i=0;i<4;i++)
  {
    h=analogRead(ldr[i]);
    if(h>avg[i])
    {
    digitalWrite(ledpin[i],HIGH);
    count++;
    }
    else
    digitalWrite(ledpin[i],LOW);
    ledpin[i]=z[i];
  }
  for(int i=0;i<4;i++)
  {
    if(z[i]==HIGH)
    {
      i+=sum;sum=i;
      d[i]+=fum;
      fum=d[i];
    }
  }
  dir=sum/count;
  meandir=fum/count;
  myservo.write(90+meandir);
  count=0;
  sum=0;
  fum=0;
}

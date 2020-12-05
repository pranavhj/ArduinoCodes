
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

float x=100000000;



  for( int i=0;i>=0;i++)
{if(x==1)
{break;}


if(x%2==0)
{x=x/2;Serial.println(x);}

else
{x=3*x+1;Serial.println(x);}
}
}

void loop() {
  // put your main code here, to run repeatedly:


}



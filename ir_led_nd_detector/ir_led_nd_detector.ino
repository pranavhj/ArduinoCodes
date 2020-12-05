int detect=2;int m=9;int detect1=3;
int ledpin=13;int ledpin1=9;volatile int encoder0Pos=0;int last=0;
void setup() {
  // put your setup code here, to run once:
pinMode(detect,INPUT);pinMode(detect1,INPUT);
pinMode(m,OUTPUT);
pinMode(13,OUTPUT);pinMode(9,OUTPUT);Serial.begin(9600);
digitalWrite(m,HIGH);
//attachInterrupt(digitalPinToInterrupt(2),doEncoder,FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
int a=digitalRead(detect);digitalWrite(13,a);

int b=digitalRead(detect1);digitalWrite(9,b);
//if(encoder0Pos==last)
//Serial.println(encoder0Pos);
//last=encoder0Pos;



}
//void doEncoder()
  //{encoder0Pos++;digitalWrite(13,HIGH);}

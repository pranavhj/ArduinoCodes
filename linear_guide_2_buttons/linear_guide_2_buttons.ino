int motorpinleft=8;
int motorpinright=9;
int button1=6;
int button2=7;


void setup() {
  // put your setup code here, to run once:
  pinMode(motorpinleft,OUTPUT);
   pinMode(motorpinright,OUTPUT);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motorpinleft,LOW);
  digitalWrite(motorpinright,LOW);
  Serial.print(digitalRead(button1));Serial.print("           "); Serial.println(digitalRead(button2));
  if(digitalRead(button1)==HIGH)

        {digitalWrite(motorpinleft,HIGH);
        digitalWrite(motorpinright,LOW);delay(20);}


//  if(digitalRead(button2)==HIGH)

        {digitalWrite(motorpinleft,LOW);
        digitalWrite(motorpinright,HIGH);delay(20);}
       




}




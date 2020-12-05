const int stepPin_1 = 10; 
const int dirPin_1= 2; 
void setup() {
  // put your setup code here, to run once:
pinMode(stepPin_1,OUTPUT); 
  pinMode(dirPin_1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(dirPin_1,LOW);


{   digitalWrite(stepPin_1,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin_1,LOW);
    delayMicroseconds(2000);
  
  }
}

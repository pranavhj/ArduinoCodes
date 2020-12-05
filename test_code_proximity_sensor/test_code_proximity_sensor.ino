int sensorpin=2;
volatile int counter=0;
void setup() {
  // put your setup code here, to run once:
pinMode(2,INPUT);
Serial.begin(9600);
attachInterrupt(digitalPinToInterrupt(2),increment,CHANGE);}

void loop() {
  // put your main code here, to run repeatedly:


}
void increment()
 {counter++;
 Serial.println(counter);delay(50);}

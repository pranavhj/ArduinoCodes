#define trig 9
#define echo 8
long duration,distance;


void setup() {
  // put your setup code here, to run once:
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trig,LOW);
delay(2);

duration=pulseIn(echo,HIGH);
distance=duration/58;
Serial.println(distance);
delay(200);

}

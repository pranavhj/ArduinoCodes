int dtpin=2;
int clkpin=22; 


void setup() {
  // put your setup code here, to run once:
pinMode(dtpin,INPUT);
pinMode(clkpin,INPUT);


Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int cl=digitalRead(dtpin);
int dt=digitalRead(clkpin);
Serial.print(dt);Serial.print("    ");Serial.println(cl);
if(dt!=cl)
{
}
}

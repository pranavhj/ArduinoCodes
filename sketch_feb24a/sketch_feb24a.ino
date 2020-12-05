int p1=9;
int p=10;

void setup() {
  // put your setup code here, to run once:
pinMode(p1,OUTPUT);
pinMode(p,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(p1,100);
analogWrite(p,100);
}

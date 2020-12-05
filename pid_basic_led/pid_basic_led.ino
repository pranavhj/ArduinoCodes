#include <PID_v1.h>
int ledpin=9;
int ldrpin=0;
double setpoint,input,output;
PID mypid(&input,&output,&setpoint,0,10,0,DIRECT);



void setup() {
// put your setup code here, to run once:
Serial.begin(9600);pinMode(ledpin,OUTPUT);pinMode(ldrpin,INPUT);
input=analogRead(ldrpin);
mypid.SetMode(AUTOMATIC);
setpoint=22;

}

void loop() {
  // put your main code here, to run repeatedly:
input=analogRead(ldrpin);
Serial.print(input);
mypid.Compute();Serial.print("     ");Serial.println(output);
output=constrain(output,0,150);
analogWrite(ledpin,output);
}

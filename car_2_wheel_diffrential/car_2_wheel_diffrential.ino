int enc1=0;
int enc2=2;
int motor1_fw=7;
int motor1_afw=8;
int motor1_pwm=5;

int motor2_fw=9;
int motor2_afw=10;
int motor2_pwm=6;


void setup() {
  // put your setup code here, to run once:
  pinMode(enc1,INPUT);
  pinMode(enc2,INPUT);
  pinMode(motor1_fw,OUTPUT);
  pinMode(motor1_afw,OUTPUT);
  pinMode(motor2_fw,OUTPUT);
  pinMode(motor2_afw,OUTPUT);
  
  
  Serial.begin(9600);
  Serial.println("start");

}

void loop() {
  // put your main code here, to run repeatedly
  Serial.print(analogRead(enc1));
  Serial.print("        ");
  Serial.println(analogRead(enc2));

   digitalWrite(motor1_fw,HIGH);
   digitalWrite(motor1_afw,LOW);
   analogWrite(motor1_pwm,255);


   digitalWrite(motor2_fw,HIGH);
   digitalWrite(motor2_afw,LOW);
   analogWrite(motor2_pwm,255);

}

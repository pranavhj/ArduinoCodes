int pwm_pin_1=8;
int input_1_1=9;
int input_2_1=10;



int pwm_pin_2=7;
int input_1_2=11;
int input_2_2=12;
int enc_1=2;
void setup() {
  // put your setup code here, to run once:
pinMode(input_1_1,OUTPUT);
pinMode(input_2_1,OUTPUT);
pinMode(pwm_pin_1,OUTPUT);


pinMode(input_1_2,OUTPUT);
pinMode(input_2_2,OUTPUT);
pinMode(pwm_pin_2,OUTPUT);
pinMode(enc_1,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(input_1_1,HIGH);
digitalWrite(input_2_1,LOW);
analogWrite(pwm_pin_1,70);


digitalWrite(input_1_2,HIGH);
digitalWrite(input_2_2,LOW);
analogWrite(pwm_pin_2,90);



delay(300);



digitalWrite(input_1_1,LOW);
digitalWrite(input_2_1,HIGH);
analogWrite(pwm_pin_1,70);

digitalWrite(input_1_2,LOW);
digitalWrite(input_2_2,HIGH);
analogWrite(pwm_pin_1,90);

delay(300);
Serial.println(analogRead(enc_1));
}


int motor_1_cw=22;
int motor_1_acw=23;
int motor_4_cw=24;
int motor_4_acw=25;
int motor_3_cw=26;
int motor_3_acw=27;
int motor_2_cw=28;
int motor_2_acw=29;


int motor_1_pwm=8;
int motor_4_pwm=9;
int motor_3_pwm=10;
int motor_2_pwm=11;



void setup() {
  // put your setup code here, to run once:
pinMode(motor_1_cw,OUTPUT);
pinMode(motor_1_acw,OUTPUT);
pinMode(motor_2_cw,OUTPUT);
pinMode(motor_2_acw,OUTPUT);
pinMode(motor_3_cw,OUTPUT);
pinMode(motor_3_acw,OUTPUT);
pinMode(motor_4_cw,OUTPUT);
pinMode(motor_4_acw,OUTPUT);



pinMode(motor_1_pwm,OUTPUT);
pinMode(motor_2_pwm,OUTPUT);
pinMode(motor_3_pwm,OUTPUT);
pinMode(motor_4_pwm,OUTPUT);
}

void loop() {int dir=0;
  // put your main code here, to run repeatedly:
{digitalWrite(motor_1_cw,LOW);                                   //all motor sidha
 digitalWrite(motor_1_acw,HIGH);
 digitalWrite(motor_1_pwm,255);}

{digitalWrite(motor_2_cw,LOW);
 digitalWrite(motor_2_acw,HIGH);
 digitalWrite(motor_2_pwm,255);}


 {digitalWrite(motor_3_cw,LOW);
 digitalWrite(motor_3_acw,HIGH);
 digitalWrite(motor_3_pwm,255);}



{digitalWrite(motor_4_cw,LOW);
 digitalWrite(motor_4_acw,HIGH);
 digitalWrite(motor_4_pwm,255);}

}


int enc_1=0;
int enc_2=1;

int motor_1_fw=22;
int motor_1_bw=23;
int motor_2_fw=26;
int motor_2_bw=27;


int motor_1_pwm=8;
int motor_2_pwm=9;



int initial_pos_1=0;
int current_pos_1=0;
float steps_1=0;
int enc_steps_1(int,int,float);
int flag_1=0;



int initial_pos_2=0;
int current_pos_2=0;
float steps_2=0;
int enc_steps_2(int,int,float);
int flag_2=0;


int prev_steps_1=0;
int prev_time_1=0;


int prev_steps_2=0;
int prev_time_2=0;
char q='s';


void setup() {
  // put your setup code here, to run once:
pinMode(enc_1,INPUT);
pinMode(enc_2,INPUT);


pinMode(motor_1_fw,OUTPUT);
pinMode(motor_1_bw,OUTPUT);
pinMode(motor_2_fw,OUTPUT);
pinMode(motor_2_bw,OUTPUT);
pinMode(motor_1_pwm,OUTPUT);
pinMode(motor_2_pwm,OUTPUT);


initial_pos_1=analogRead(enc_1);
initial_pos_2=analogRead(enc_2);




Serial.begin(9600);
Serial.println("start");
}

void loop() {
 

current_pos_1=analogRead(enc_1);
steps_1=enc_steps_1(current_pos_1,initial_pos_1,steps_1);{  initial_pos_1=current_pos_1;}



current_pos_2=analogRead(enc_2);
steps_2=enc_steps_2(current_pos_2,initial_pos_2,steps_2);{  initial_pos_2=current_pos_2;}

//Serial.print(steps_1);Serial.print("               ");Serial.println(steps_2);


float speed_1=(steps_1-prev_steps_1)/(millis()-prev_time_1);
float speed_2=(steps_2-prev_steps_2)/(millis()-prev_time_2);


Serial.print(speed_1/1017*1000*60);Serial.print("               ");Serial.println(speed_2/980*1000*60);





prev_steps_1=steps_1;
prev_steps_2=steps_2;

prev_time_1=millis();
prev_time_2=millis();

if(Serial.available()>0)
  { q=Serial.read();}
  
  

if(steps_1<8000  &&   q=='q')
{motors_start();}


else
{motors_stop();}



delay(300);


//Serial.print(avg_speed_1/30*100);Serial.print("             ");Serial.println(avg_speed_2/30*100);


//Serial.println(steps_1-steps_2);




}




int enc_steps_1(int cp,int ip,float s)
{ flag_1=0;

  if(cp>ip+2  ||  cp+2<ip  )
  {digitalWrite(13,HIGH);
    if(cp>ip)
    {   if(cp>ip+480)
             {s=s-(ip+1+982-cp);}
        else
      {s=s+(cp-ip);}
      }

   if(cp<ip)
    {   if(cp+480<ip)
             {s=s+(cp+1+982-ip);}
        else
              {s=s-(ip-cp);}
              }
    
    
   
   // Serial.print(s);Serial.print("                   ");
    delay(10);
  
    flag_1=1;

   
   
 

  }
   return(s);
}




int enc_steps_2(int cp,int ip,float s)
{ flag_2=0;

  if(cp>ip+2  ||  cp+2<ip  )
  {digitalWrite(13,HIGH);
    if(cp>ip)
    {   if(cp>ip+480)
             {s=s-(ip+1+982-cp);}
        else
      {s=s+(cp-ip);}
      }

   if(cp<ip)
    {   if(cp+480<ip)
             {s=s+(cp+1+982-ip);}
        else
              {s=s-(ip-cp);}
              }
    
    
   
   // Serial.println(s);
    delay(10);
  
    flag_2=1;

   
   
 

  }
   return(s);
}

int motors_start()
{digitalWrite(motor_1_fw,LOW);
digitalWrite(motor_1_bw,HIGH);
analogWrite(motor_1_pwm,240);


digitalWrite(motor_2_fw,HIGH);
digitalWrite(motor_2_bw,LOW);
analogWrite(motor_2_pwm,227);}


int motors_stop()
{digitalWrite(motor_1_fw,LOW);
digitalWrite(motor_1_bw,HIGH);
analogWrite(motor_1_pwm,0);


digitalWrite(motor_2_fw,HIGH);
digitalWrite(motor_2_bw,LOW);
analogWrite(motor_2_pwm,0);
}



//delete flags

int enc_1=0;
int enc_2=1;                        //enc intitialization

int motor_1_fw=9;
int motor_1_bw=8;         
int motor_2_fw=27;                  //motor intitialization
int motor_2_bw=26;


int motor_1_pwm=7;
int motor_2_pwm=9;                   //motor intitialization 



int initial_pos_1=0;
int current_pos_1=0;
float steps_1=0;                                //steps func intitialization for 1st enc
int enc_steps_1(int,int,float,int);




int initial_pos_2=0;
int current_pos_2=0;                            //steps func intitialization for 2nd enc
float steps_2=0;


int f;
float t=979;




                                    //1530      1468

int target_2=-979*0;int old_target_2=0;int t2;
float kp_2=0.248 , ki_2=0.00687, kd_2=0;
boolean a_2=LOW,b_2=LOW;int pwmval_2=0;              //pid initialization enc 2

int pidfunc_2(int,int,int);




int target_1=1020*0;int old_target_1=0;int t1;
float kp_1=0.248, ki_1=0.006871, kd_1=0;
boolean a_1=LOW,b_1=LOW;int pwmval_1=0;              //pid initialization enc 1

float q;                                               //gyro initialization
float yaw;
float initial_yaw;
float target_yaw=0;
float kp_g=2, ki_g=0.05, kd_g=0;


int pidfunc_1(int,int,int);
void drive_enc();
void target_func();
void gyro_drive();
float gyro_pid_func(float);
void pid_parameter();

int initial_timer=millis();
int final_timer=millis();
int brake_timer_1=millis();
int brake_timer_2=millis();


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
pinMode(13,OUTPUT);


initial_pos_1=analogRead(enc_1);
initial_pos_2=analogRead(enc_2);

Serial.begin(9600);
Serial.println("start");

Serial3.begin(250000);
//Serial3.println("start");
//delay(15000);


if(Serial3.available()>0)
{initial_yaw=Serial.read();}
 yaw=initial_yaw;
 Serial3.flush();
}

void loop() {//Serial.print(target_1);Serial.print("        ");Serial.println(target_2);
  // put your main code here, to run repeatedly:
  
 

target_func();




current_pos_1=analogRead(enc_1);
steps_1=enc_steps(current_pos_1,initial_pos_1,steps_1,0);{  initial_pos_1=current_pos_1;}Serial.print(steps_1);Serial.print("          ");


current_pos_2=analogRead(enc_2);
steps_2=enc_steps(current_pos_2,initial_pos_2,steps_2,1);{  initial_pos_2=current_pos_2;}Serial.print(steps_2);Serial.print("          ");Serial.print(target_1);Serial.print("          ");Serial.println(target_2);



pwmval_2=pidfunc_2(steps_2,target_2,pwmval_2);
pwmval_1=pidfunc_1(steps_1,target_1,pwmval_1);
drive_enc();

digitalWrite(13,LOW);

if(Serial3.available()>0)
{yaw=Serial3.read();}
q=gyro_pid_func(target_yaw);//Serial.println(yaw);


//gyro_drive();


}




int enc_steps(int cp,int ip,float s,int l)
{ 
  int ref_vol;
  if(l=0)
  {ref_vol=1020;}
  else
  {ref_vol=979;}

  if(cp>ip+2  ||  cp+2<ip  )
  {digitalWrite(13,HIGH);
    if(cp>ip)
    {   if(cp>ip+480)
             {s=s-(ip+1+ref_vol-cp);}
        else
      {s=s+(cp-ip);}
      }

   if(cp<ip)
    {   if(cp+480<ip)
             {s=s+(cp+1+ref_vol-ip);}
        else
              {s=s-(ip-cp);}
              }
    
    
   
    //Serial.print(s);Serial.print("                   ");
    delay(10);

  }
   return(s);
}




int pidfunc_2(int currentvalue,int targetvalue,int pwmvalue)

 {
   pwmvalue=0;
    int error=targetvalue-currentvalue;static int lasterror=0;static float totalerror=160;
    float pidterm=0;
    
    if(currentvalue==0   &&   targetvalue==0     &&    pwmvalue==0)
    {totalerror=0;}

     if(error>0)
    {a_2=HIGH;b_2=LOW;}
    else
    {a_2=LOW;b_2=HIGH;}

    totalerror=totalerror+(error);//Serial.println(totalerror);
    pidterm=kp_2*(error)+ki_2*(totalerror)+kd_2*(error-lasterror);totalerror=constrain(totalerror,-18500,18500);
    lasterror=error;pidterm=abs(pidterm);
    //Serial.print(constrain(abs(pwmvalue+pidterm),0,235));Serial.print("          ");
    //Serial.println(error);Serial.print("      ");
    
    return(constrain((pwmvalue+pidterm),0,255));
   
   }




int pidfunc_1(int currentvalue,int targetvalue,int pwmvalue)

 {
   pwmvalue=0;
    int error=targetvalue-currentvalue;static int lasterror=0;static float totalerror=0;
    float pidterm=0;
  


      if(currentvalue==0   &&   targetvalue==0     &&    pwmvalue==0)
    {totalerror=0;}
  
     
     if(error>0)
    {a_1=HIGH;b_1=LOW;}
    else
    {a_1=LOW;b_1=HIGH;}
    
    
    totalerror=totalerror+(error);totalerror=constrain(totalerror,-18500,18500);
    pidterm=kp_1*(error)+ki_1*(totalerror)+kd_1*(error-lasterror);
    lasterror=error;pidterm=abs(pidterm);
    //Serial.print(constrain(abs(pwmvalue+pidterm),0,235));Serial.print("          ");
    //Serial.println(error);Serial.print("      ");
   
    return(constrain((pwmvalue+pidterm),0,255));
   
   }




void drive_enc()
{//if(t1>(millis()-brake_timer_1)   ||   t2>(millis()-brake_timer_2))
if(abs(target_2-steps_2)>30   ||  abs(target_1-steps_1)>30)
{digitalWrite(motor_1_fw,a_1);
digitalWrite(motor_1_bw,b_1);
analogWrite(motor_1_pwm,pwmval_1);//Serial.print(pwmval_1);Serial.print("          ");

digitalWrite(motor_2_fw,a_2);
digitalWrite(motor_2_bw,b_2);
analogWrite(motor_2_pwm,pwmval_2);//Serial.println(pwmval_2);
}

else
drive_brake();

}




void target_func()
{if(Serial.available()>0)
{int s=Serial.read();
if(s=='q')
{old_target_1=target_1;old_target_2=target_2;
target_1=target_1+1000+(1000/1020*41);
target_2=target_2-1000;

}
if(s=='r')
{old_target_1=target_1;old_target_2=target_2;
target_1=target_1-1000+(1000/1020*41);
target_2=target_2+1000;}
if(s=='t')
{old_target_1=target_1;old_target_2=target_2;
target_1=target_1+820;
target_2=target_2+970;}
if(s=='s')
{old_target_1=target_1;old_target_2=target_2;
target_1=target_1-820;
target_2=target_2-970;}
int m1=pidfunc_2(0,0,0);
int m2=pidfunc_1(0,0,0);
t1=abs(target_1-old_target_1)*15;
t2=abs(target_2-old_target_2)*15;
brake_timer_1=millis();
brake_timer_2=millis();}
}







float gyro_pid_func(float target_yaw)
{float currentvalue=yaw-initial_yaw;
float error=currentvalue-target_yaw; static int lasterror=0;static float totalerror=0;
float pidterm=0;
 totalerror=totalerror+(error);totalerror=constrain(totalerror,-1700,1700);
    pidterm=kp_g*(error)+ki_g*(totalerror)+kd_g*(error-lasterror);
    lasterror=error;//pidterm=abs(pidterm);
    
return(constrain((pidterm),-50,50));

}





void gyro_drive()
{
  if(steps_1<8000)
  {digitalWrite(motor_1_fw,1);
digitalWrite(motor_1_bw,0);
analogWrite(motor_1_pwm,200+q);//Serial.print(pwmval_1);Serial.print("          ");



digitalWrite(motor_2_fw,0);
digitalWrite(motor_2_bw,1);
analogWrite(motor_2_pwm,200-q);//Serial.println(pwmval_2);}
  }

else
drive_brake();
}




void drive_brake()
{digitalWrite(motor_1_fw,1);
digitalWrite(motor_1_bw,0);
analogWrite(motor_1_pwm,0);//Serial.print(pwmval_1);Serial.print("          ");



digitalWrite(motor_2_fw,0);
digitalWrite(motor_2_bw,1);
analogWrite(motor_2_pwm,0);//Serial.println(pwmval_2);
}



void pid_parameter()
{ if(target_1>1000   ||    target_1<-1000)   
  
  {//kp_1=0.240; ki_1=0.007871; kd_1=0.00105;
   kp_1=0.212-abs(target_1/500000); ki_1=0.009571-abs(target_1/500000); kd_1=0.00105;
   }
  else
  {kp_1=0.210; ki_1=0.009571; kd_1=0.00105;
    }

  if(target_2>1000   ||    target_2<-1000)
  {//kp_2=0.212 ; ki_2=0.00797; kd_2=0.001;
   kp_2=0.244-abs(target_2/500000) ; ki_2=0.00817-abs(target_1/500000); kd_2=0.00105;
  }
  else
  {kp_2=0.242 ; ki_2=0.00797; kd_2=0.001;
  }
  }

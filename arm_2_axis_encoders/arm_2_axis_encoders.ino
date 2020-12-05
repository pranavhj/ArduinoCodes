//delete flags

int enc_1=0;
int enc_2=3;                        //enc intitialization

int motor_1_fw=9;
int motor_1_bw=10;         
int motor_2_fw=12;                  //motor intitialization
int motor_2_bw=11;


int motor_1_pwm=8;
int motor_2_pwm=7;                   //motor intitialization 



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

double target_2=0;int old_target_2=0;int t2;
float kp_2=2.1 , ki_2=0.0570, kd_2=2.5;
boolean a_2=LOW,b_2=LOW;int pwmval_2=0;              //pid initialization enc 2

int pidfunc_2(int,int,int);




double target_1=0;int old_target_1=0;int t1;
float kp_1=1.9/1.5, ki_1=0.038, kd_1=1;
boolean a_1=LOW,b_1=LOW;int pwmval_1=0;              //pid initialization enc 1




int pidfunc_1(int,int,int);
void drive_enc();
void target_func();
void pid_parameter();

int initial_timer=millis();
int final_timer=millis();
int brake_timer_1=millis();
int brake_timer_2=millis();


int calibration_flag=1;


double x1=370;
double y1=0;
float x[100];                                        //linear interpolation initialization
float y[100];
double theta11[100];
double theta21[100];
int i=0;
double target_timer=0;
int z=1;
int d=0;


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

double y2=200;                                                 //equatoin of line

for(double m=0;m<36;m=m+1)
{y[i]=m;                                                     //getting x,y co-ordinates of points
x[i]=250;
i++; 
}


for(int l=0;l<i;l++)
{x1=x[l];
y1=y[l];  
double theta2=acos(((x1*x1)+(y1*y1)-72148)/32376/2)*180/3.142;
double theta1=(atan2(y1,x1)-atan2(228*sin(theta2),(142+(228*cos(theta2)))))*180/3.142;                 //getting values of joint angles
Serial.print(theta1);Serial.print("           ");Serial.print(theta2);Serial.print("           ");Serial.print(x1);Serial.print("           ");Serial.println(y1);
theta11[l]=theta1;
theta21[l]=theta2;
}
Serial.println("start");

target_1=-theta21[0]*952/90;
target_2=-theta11[0]*912/90;
target_timer=millis();

}

void loop() {//Serial.print(target_1);Serial.print("        ");Serial.println(target_2);
  // put your main code here, to run repeatedly:
  
 

target_func();
//pid_parameters();




current_pos_1=analogRead(enc_1);
steps_1=enc_steps(current_pos_1,initial_pos_1,steps_1,0);{  initial_pos_1=current_pos_1;}Serial.print(steps_1);Serial.print("          ");


current_pos_2=analogRead(enc_2);
steps_2=enc_steps(current_pos_2,initial_pos_2,steps_2,1);{  initial_pos_2=current_pos_2;}Serial.print(steps_2);Serial.print("          ");Serial.print(target_1);Serial.print("          ");Serial.println(target_2);



pwmval_2=pidfunc_2(steps_2,target_2,pwmval_2);
pwmval_1=pidfunc_1(steps_1,target_1,pwmval_1);
/*if(calibration_flag<0)
{drive_brake();
steps_1=0;
steps_2=0;
initial_pos_1=analogRead(enc_1);
initial_pos_2=analogRead(enc_2);
}
else*/
{drive_enc();}







}




int enc_steps(int cp,int ip,float s,int l)
{ 
  int ref_vol;
  if(l=0)
  {ref_vol=1020;}
  else
  {ref_vol=979;}

  if(cp>ip+2  ||  cp+2<ip  )
  {
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
    pidterm=kp_2*(error)+ki_2*(totalerror)+kd_2*(error-lasterror);totalerror=constrain(totalerror,-1000,1000);
    lasterror=error;pidterm=abs(pidterm);
    //Serial.print(constrain(abs(pwmvalue+pidterm),0,235));Serial.print("          ");
    //Serial.println(error);Serial.print("      ");
    
    return(constrain((pwmvalue+pidterm),0,140));
   
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
   
    return(constrain((pwmvalue+pidterm),0,110));
   
   }




void drive_enc()
{//if(t1>(millis()-brake_timer_1)   ||   t2>(millis()-brake_timer_2))
//if((abs(target_2-steps_2)>3   ||  abs(target_1-steps_1)>3))
{digitalWrite(motor_1_fw,a_1);
digitalWrite(motor_1_bw,b_1);
analogWrite(motor_1_pwm,pwmval_1);//Serial.print(pwmval_1);Serial.print("          ");

digitalWrite(motor_2_fw,a_2);
digitalWrite(motor_2_bw,b_2);
analogWrite(motor_2_pwm,pwmval_2);//Serial.println(pwmval_2);
}

//else
{//drive_brake();
  }
}





void target_func()
{/*if(Serial.available()>0)
{int s=Serial.read();

if(s=='q')
{old_target_1=target_1;
target_1=target_1+(10);
}

if(s=='r')
{old_target_2=target_2;

target_2=target_2+(10);}

if(s=='t')
{old_target_1=target_1;
target_1=target_1-(10);
}

if(s=='s')
{old_target_2=target_2;
target_2=target_2-(10);}



if(s=='c');
{calibration_flag=calibration_flag*(-1);}
*/

int target_first_timer=millis();


int target_timer_2=millis();
if(target_timer_2>target_timer+2000   &&   d==0   &&    target_first_timer>10000)
{old_target_1=target_1;
old_target_2=target_2;
 target_1=-theta21[z]*952/90;
target_2=-theta11[z]*912/90;
target_timer=millis();
z++;
if(z==i)
{d++;}
}

int m1=pidfunc_2(0,0,0);
int m2=pidfunc_1(0,0,0);
t1=abs(target_1-old_target_1)*15;
t2=abs(target_2-old_target_2)*15;
brake_timer_1=millis();
brake_timer_2=millis();
}


void drive_brake()
{digitalWrite(motor_1_fw,1);
digitalWrite(motor_1_bw,0);
analogWrite(motor_1_pwm,0);//Serial.print(pwmval_1);Serial.print("          ");

digitalWrite(motor_2_fw,0);
digitalWrite(motor_2_bw,1);
analogWrite(motor_2_pwm,0);//Serial.println(pwmval_2);
}


/*void pid_parameters()
{if(abs(target_1-old_target_1)>200)
   {kp_1=0.139/2.5;  ki_1=0.01/2;   kd_1=0.2   ;                                            //p to p
    digitalWrite(13,HIGH);}
  else
   {kp_1=1; ki_1=0.0006 /; kd_1=0;                                                //interpolation
    digitalWrite(13,LOW);}
  if(abs(target_2-old_target_2)>200)
  {kp_2=0.6/2.5;  ki_2=0.0470/2;  kd_2=0.2;                                                //p to p
   digitalWrite(13,HIGH);}
  else
  { kp_2=1.4 ; ki_2=0.008; kd_2=0.1;
  digitalWrite(13,LOW);}                                               //interpolation  
 }*/
 

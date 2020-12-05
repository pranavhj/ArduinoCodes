//delete flags

int enc_1=3;
int enc_2=0;                        //enc intitialization

int motor_2_fw=28;
int motor_2_bw=26;         
int motor_1_fw=32;                  //motor intitialization
int motor_1_bw=30;
int motor_3_fw=36;
int motor_3_bw=37;


int motor_2_pwm=4;
int motor_1_pwm=5;                   //motor intitialization 
int motor_3_pwm=6;

int led_pin_1=52;
int led_pin_2=50;
int led_pin_3=48;
int led_pin_4=46;


int initial_pos_1=0;
int current_pos_1=0;
double steps_1=0;                                //steps func intitialization for 1st enc
double enc_steps_1(int,int,double,int);




int initial_pos_2=0;
int current_pos_2=0;                            //steps func intitialization for 2nd enc
double steps_2=0;


int f;
double t=979;




                                    //1530      1468

double target_2=00;double old_target_2=0;int t2;
double kp_2=1.7 , ki_2=0.025, kd_2=1;
boolean a_2=LOW,b_2=LOW;int pwmval_2=0;              //pid initialization enc 2

int pidfunc_2(int,int,int);




double target_1=00;int old_target_1=0;int t1;
float kp_1=1.4, ki_1=0.035, kd_1=0.9;
boolean a_1=LOW,b_1=LOW;int pwmval_1=0;              //pid initialization enc 1




double target_3=00;int old_target_3=0;int t3;
float kp_3=1.4, ki_3=0.035, kd_3=0.9;
boolean a_3=LOW,b_3=LOW;int pwmval_3=0; 



int pidfunc_1(int,int,int);
void drive_enc();
void target_func();
void pid_parameter();




int calibration_flag=1;

double line_x=0, line_y=0;



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
pinMode(motor_3_fw,OUTPUT);
pinMode(motor_3_bw,OUTPUT);
pinMode(13,OUTPUT);

pinMode(led_pin_1,OUTPUT);
pinMode(led_pin_2,OUTPUT);
pinMode(led_pin_3,OUTPUT);
pinMode(led_pin_4,OUTPUT);


initial_pos_1=analogRead(enc_1);
initial_pos_2=analogRead(enc_2);

Serial.begin(9600);
Serial.println("start");


noInterrupts();           // disable all interrupts

  TCCR1A = 0;

  TCCR1B = 0;

  TCNT1  = 0;


  OCR1A = 31250/5;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler 

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();             // enable all interrupts

//target_timer=millis();
//digitalWrite(led_pin_1,HIGH);
//digitalWrite(led_pin_2,HIGH);
//digitalWrite(led_pin_3,HIGH);
//digitalWrite(led_pin_4,HIGH);




}

void loop() {
if(Serial.available()>0)
{char s=Serial.read();

if(s=='q')
{//target_1=target_1+1000;
//target_2=target_2+1000;
goto_func(240,0);
  s='p';}

if(s=='r')
{//target_1=target_1+1000;
//target_2=target_2+1000;
goto_func(-240,0);
  s='p';}  
  


if(s=='z')
{steps_1=0;
steps_2=0;
target_1=0;
target_2=0;
  s='p';}  

if(s=='l')
{draw_line(0,0,-240,0);
  s='p';}

if(s=='0')
{goto_func(0,0);
  s='p';}
  
  }

digitalWrite(13,LOW);


stepper_run();

}




double enc_steps(int cp,int ip,double s,int l)
{ 
  int ref_vol;
  if(l=0)
  {ref_vol=1004;}
  else
  {ref_vol=960;}

  if(cp>ip+2  ||  cp+2<ip  )
  {
    if(cp>ip)
    {   if(cp>ip+700)
             {s=s-(ip+1+ref_vol-cp);}
        else
      {s=s+(cp-ip);}
      }

   if(cp<ip)
    {   if(cp+700<ip)
             {s=s+(cp+1+ref_vol-ip);}
        else
              {s=s-(ip-cp);}
              }
    
    
   
    //Serial.print(s);Serial.print("                   ");
    delay(10);

  }
   return(s);
}




int pidfunc_2(double currentvalue,double targetvalue,int pwmvalue)

 {
   pwmvalue=0;
    double error=targetvalue-currentvalue;static double lasterror=0;static double totalerror=0;
    double pidterm=0;
   if((old_target_2!=target_2))
    {totalerror=0;//Serial.println("1");
    }
     old_target_2=target_2;
     if(error>0)
    {a_2=HIGH;b_2=LOW;}
    else
    {a_2=LOW;b_2=HIGH;}

    totalerror=totalerror+(error);//Serial.println(totalerror);
    pidterm=kp_2*(error)+ki_2*(totalerror)+kd_2*(error-lasterror);totalerror=constrain(totalerror,-5000,5000);
    lasterror=error;pidterm=abs(pidterm);
    //Serial.println(constrain(abs(pwmvalue+pidterm),0,235));Serial.print("          ");
    //Serial.println(totalerror);Serial.print("      ");
    //pidterm=int(pidterm);
    return(constrain(pwmvalue+pidterm,0,250)); 
   }




int pidfunc_1(double currentvalue,double targetvalue,int pwmvalue)

 {
   pwmvalue=0;
    double error=targetvalue-currentvalue;static double lasterror=0;static double totalerror=0;
    double pidterm=0;
  
      if( (old_target_1!=target_1))
    {totalerror=0;
    }
    old_target_1=target_1;
      
    if(error>0)
    {a_1=HIGH;b_1=LOW;}
    else
    {a_1=LOW;b_1=HIGH;}
    
    totalerror=totalerror+(error);totalerror=constrain(totalerror,-5000,5000);
    pidterm=kp_1*(error)+ki_1*(totalerror)+kd_1*(error-lasterror);
    lasterror=error;pidterm=abs(pidterm);
    //Serial.print(constrain(abs(pwmvalue+pidterm),0,235));Serial.print("          ");
    //Serial.println(totalerror);Serial.print("      ");
    // pidterm=int(pidterm);
    return(constrain(pwmvalue+pidterm,0,245));
   }


/*
int pidfunc_3(double currentvalue,double targetvalue,int pwmvalue)

 {
   pwmvalue=0;
    double error=targetvalue-currentvalue;static double lasterror=0;static double totalerror=0;
    double pidterm=0;
  
      if( (old_target_3!=target_3))
    {totalerror=0;
    }
    old_target_3=target_3;
      
    if(error>0)
    {a_3=HIGH;b_3=LOW;}
    else
    {a_3=LOW;b_3=HIGH;}
    
    totalerror=totalerror+(error);totalerror=constrain(totalerror,-5000,5000);
    pidterm=kp_3*(error)+ki_3*(totalerror)+kd_3*(error-lasterror);
    lasterror=error;pidterm=abs(pidterm);
    //Serial.print(constrain(abs(pwmvalue+pidterm),0,235));Serial.print("          ");
    //Serial.println(totalerror);Serial.print("      ");
    // pidterm=int(pidterm);
    return(constrain(pwmvalue+pidterm,0,245));
   }

*/

void drive_enc()
{
digitalWrite(motor_1_fw,a_1);
digitalWrite(motor_1_bw,b_1);
analogWrite(motor_1_pwm,pwmval_1);//Serial.print(pwmval_1);Serial.print("          ");

digitalWrite(motor_2_fw,a_2);
digitalWrite(motor_2_bw,b_2);
analogWrite(motor_2_pwm,pwmval_2);//Serial.println(pwmval_2);


//digitalWrite(motor_3_fw,a_3);
//digitalWrite(motor_3_bw,b_3);
//analogWrite(motor_3_pwm,pwmval_3);//Serial.println(pwmval_3);
}



void drive_brake()
{digitalWrite(motor_1_fw,1);
digitalWrite(motor_1_bw,0);
analogWrite(motor_1_pwm,0);//Serial.print(pwmval_1);Serial.print("          ");

digitalWrite(motor_2_fw,0);
digitalWrite(motor_2_bw,1);
analogWrite(motor_2_pwm,0);//Serial.println(pwmval_2);

digitalWrite(motor_3_fw,0);
digitalWrite(motor_3_bw,1);
analogWrite(motor_3_pwm,0);//Serial.println(pwmval_2);
}




int goto_func(double x, double y)
{digitalWrite(13,HIGH);


target_1=x*987/1.25/1.01*112/113*112/113;
target_2=x*998/1.25/1.035*112/111.7*112/113;
//target_3=y_steps-steps_3;

digitalWrite(led_pin_2,LOW);
digitalWrite(led_pin_3,LOW);

if(abs(target_1-steps_1)<200   )
{pid_param_traj();//digitalWrite(led_pin_4,LOW);
}                       //0 - 350
else
{pid_param_goto();//digitalWrite(led_pin_4,HIGH);
}                                   //all others





//int timer_1=millis(), timer_2=millis();

while(1)
{
 if(abs(target_1-steps_1)<50    &&   abs(target_2-steps_2)<50 )//  ||  ((timer_2-timer_1)>abs(target_1-steps_1)+2000  &&  abs(target_1-steps_1)<70  && abs(target_2-steps_2)<150)   || (  (timer_2-timer_1)>abs(target_1-steps_1)+2000  &&  abs(target_2-steps_2)<70   && abs(target_1-steps_1)<150 )  )// &&   abs(target_3-steps_3)<20)
   {break;}
  else
  {stepper_run();}

  if(abs(target_1-steps_1)<50)
{digitalWrite(led_pin_2,HIGH);}
else
{digitalWrite(led_pin_2,LOW);}

if(abs(target_2-steps_2)<50)
{digitalWrite(led_pin_3,HIGH);}
 else
{digitalWrite(led_pin_2,LOW);}
 
 //timer_2=millis();
 //Serial.println(timer_2-timer_1);
 }
 
}



int stepper_run()
{/*current_pos_1=analogRead(enc_1);
steps_1=enc_steps(current_pos_1,initial_pos_1,steps_1,0);{  initial_pos_1=current_pos_1;}//Serial.print(steps_1);Serial.print("          ");


current_pos_2=analogRead(enc_2);
steps_2=enc_steps(current_pos_2,initial_pos_2,steps_2,1);{  initial_pos_2=current_pos_2;}//Serial.print(steps_2);Serial.print("          ");Serial.print(target_1);Serial.print("          ");Serial.println(target_2);
*/
 Serial.print(steps_1);Serial.print("      ");Serial.println(steps_2);

pwmval_2=pidfunc_2(steps_2,target_2,pwmval_2);
pwmval_1=pidfunc_1(steps_1,target_1,pwmval_1);
if(abs(target_2-steps_2)-abs(target_1-steps_1)>3000)
{pwmval_1=0;}
else if(abs(target_1-steps_1)-abs(target_2-steps_2)>3000)
{pwmval_2=0;}
drive_enc();
 
  }


int pid_param_traj()
{kp_2=2.4 ; ki_2=0.035; kd_2=1;
kp_1=2.4 ; ki_1=0.5; kd_1=0.9;}


int pid_param_goto()
{kp_2=0.65 ; ki_2=0.035; kd_2=1.3;
kp_1=0.85 ; ki_1=0.045; kd_1=1.3;}



int draw_line( double x1, double y1, double x2, double y2)
{ double slope=0;
  
   {slope=(y2-y1)/(x2-x1);}
  Serial.println(slope);
  if(slope>=1 ||   ((y2-y1)<0   && (x2-x1)==0 ) )                                //((y2-y1)<0   && (x2-x1)==0 
  {for(double i=0; i<abs(y2-y1); i=i+0.1)
  {double temp1=i*10;
    if(y2>y1)
    {line_y=y1+i;}
   else
    {line_y=y1-i;}
  line_x=((1/slope)*(line_y-y1))+x1;
  //Serial.print("hi");//Serial.print("        ");Serial.println(line_y[i*10]);
  goto_func(line_x,line_y);}
  }
  
  else
  {for(double i=0; i<abs(x2-x1); i=i+0.1)
  {double temp1=i*10;
    if(x2>x1)
    {line_x=x1+i;}
   else
    {line_x=x1-i;}
  line_y=((slope)*(line_x-x1))+y1;
  //Serial.print("hi");//Serial.print("        ");Serial.println(line_y[i]*10);
  goto_func(line_x,line_y);}
  }

   digitalWrite(led_pin_1,HIGH);
   digitalWrite(led_pin_2,HIGH);
   digitalWrite(led_pin_3,HIGH);
   digitalWrite(led_pin_4,HIGH);
   delay(500);
}



ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine

{

  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
current_pos_1=analogRead(enc_1);
steps_1=enc_steps(current_pos_1,initial_pos_1,steps_1,0);{  initial_pos_1=current_pos_1;}//Serial.print(steps_1);Serial.print("          ");


current_pos_2=analogRead(enc_2);
steps_2=enc_steps(current_pos_2,initial_pos_2,steps_2,1);{  initial_pos_2=current_pos_2;}//Serial.print(steps_2);Serial.print("          ");Serial.print(target_1);Serial.print("          ");Serial.println(target_2);
}



/*
int pid_param_traj()
{kp_2=1.4 ; ki_2=0.03; kd_2=1.2;
kp_1=0.4 ; ki_1=0.04; kd_1=1.2;}


int pid_param_goto()
{kp_2=0.6 ; ki_2=0.015; kd_2=1.5;
kp_1=0.5 ; ki_1=0.01; kd_1=1.5;}*/

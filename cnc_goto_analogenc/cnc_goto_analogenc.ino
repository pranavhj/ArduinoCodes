const int stepPin_2 = 10; 
const int dirPin_2= 11; 

const int stepPin_1 = 8;                          //8
const int dirPin_1= 9;                              //9

const int stepPin_3 = 6;                          //8
const int dirPin_3= 7;


int enc_1=3;
int initial_pos_1=0;
int current_pos_1=0;
double steps_1=0;
double enc_steps(int,int,int);
int flag_1=0;
double current_1_enc=0;


 
const int led_Pin=13;
int stepper(int, int, int, int);           // steps  speed  direction   motor

double current_1=0;
double current_2=0;
double current_3=0;



double line_x[200];
double line_y[200];

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin_1,OUTPUT); 
  pinMode(dirPin_1,OUTPUT);
  pinMode(stepPin_2,OUTPUT); 
  pinMode(dirPin_2,OUTPUT);
  pinMode(stepPin_3,OUTPUT); 
  pinMode(dirPin_3,OUTPUT);
  pinMode(led_Pin,OUTPUT);
  pinMode(enc_1,INPUT);
  initial_pos_1=analogRead(enc_1);      


int m=0;

pinMode(enc_1,INPUT);
initial_pos_1=analogRead(enc_1);

Serial.begin(9600);
//stepper(1,1000,0,0);
//stepper(1,1000,0,1);
digitalWrite(led_Pin,LOW);



}



void loop() {
int temp_steps=200*56/15;
digitalWrite(led_Pin,HIGH);
if(Serial.available()>0)
{char s='p';
s=Serial.read();
if(s=='q')
{for( int i=0; i<temp_steps; i++)
{stepper(1,800,0,0);
//stepper(1,800,1,1);
digitalWrite(led_Pin,HIGH);}
s='p';

}

if(s=='r')
{for( int i=0; i<temp_steps; i++)
{stepper(1,800,1,0);
//stepper(1,800,0,1);
digitalWrite(led_Pin,HIGH);}
s='p';

}

if(s=='s')
{for( int i=0; i<temp_steps; i++)
 {stepper(1,800,1,1);
digitalWrite(led_Pin,HIGH);}
s='p';
}

if(s=='d')
{for( int i=0; i<temp_steps; i++)
  {stepper(1,800,0,1);
digitalWrite(led_Pin,HIGH);}
s='p';
}


if(s=='z')
{for( int i=0; i<temp_steps; i++)
 {stepper(1,800,0,2);
digitalWrite(led_Pin,HIGH);}
s='p';}

if(s=='x')
{for( int i=0; i<temp_steps; i++)
  {stepper(1,800,1,2);
digitalWrite(led_Pin,HIGH);}
s='p';}


if(s=='m')
{goto_func(-4,-4);
s='p';}

if(s=='n')
{goto_func(0,0);
s='p';}

if(s=='f')
{goto_func(26,26);
s='p';}

if(s=='l')
{draw_line(0,0,36,20);
s='p';
}


 
/*stepper(97,3000,1);
delay(3000);
stepper(97,3000,0);
delay(3000);*/

//stepper(97,800,0,0);
//stepper(97,800,0,1);

//Serial.print(current_1/15.08888);Serial.print("          ");Serial.println(current_2/15.088888);

}
}


int stepper( int steps, int rpm, int rotn_direc, int motor)
{int m=0;
digitalWrite(dirPin_1,rotn_direc);
digitalWrite(dirPin_2,rotn_direc);
digitalWrite(dirPin_3,rotn_direc);
int temp=89;

//current_pos_1=analogRead(enc_1);
//steps_1=enc_steps(current_pos_1,initial_pos_1,steps_1);if(flag_1==1){  initial_pos_1=current_pos_1;}
//current_1_enc=steps_1*200*56/15/982;


if(motor==0)
{temp=stepPin_1;
if(rotn_direc==0)
{current_1=current_1-steps;}
if(rotn_direc==1)
{current_1=current_1+steps;}
}

if(motor==1)
{temp=stepPin_2;
if(rotn_direc==0)
{current_2=current_2+steps;}
if(rotn_direc==1)
{current_2=current_2-steps;}
}


if(motor==2)
{temp=stepPin_3;
if(rotn_direc==0)
{current_3=current_3+steps;}
if(rotn_direc==1)
{current_3=current_3-steps;}
}



//Serial.print(current_1);Serial.print("  ");Serial.println(current_2);
//Serial.println(current_1_enc);

while(m<steps)
{   digitalWrite(temp,HIGH);
    delayMicroseconds(rpm);
    digitalWrite(temp,LOW);
    delayMicroseconds(rpm);
  m++;
  }
}





int goto_func(int x , int y)

{
 
double target_1=x*200/1.25*56/15;
double target_2=x*200/1.25*56/15;
double target_3=y*200/1.25*56/15;

//Serial.println(target_1);Serial.println(target_3);

int temp_rotn_direc_1=0;
int temp_rotn_direc_2=1;
int temp_rotn_direc_3=1;

if( target_1-current_1>=0  )
{temp_rotn_direc_1=1;}                              //change to proper val
if( target_2-current_2>0)
{temp_rotn_direc_2=0;}
if( target_3-current_3>0)
{temp_rotn_direc_3=0;}



int flag_1=0, flag_2=0, flag_3=0, flag=0;
while(1)
{//Serial.println(current_1_enc);
  
  if(abs(current_1-current_1_enc)>1000)
  {current_1=current_1_enc;
  }
  
  if(flag_1==1    &&    flag_2==1   &&   flag_3==1)
  {break;}
  
  flag=flag_1+flag_2+flag_3;
  int stepper_delay=400/(3-flag);
  //Serial.println(stepper_delay);
  if((current_1)!=(target_1)   &&  abs(current_1-target_1)>1)
  {stepper(1,stepper_delay,temp_rotn_direc_1,0);}
  else
  {flag_1=1;}
  if(abs(current_2)!=abs(target_2)    &&   abs(current_2-target_2)>1)
  {stepper(1,stepper_delay,temp_rotn_direc_2,1);}
  else
  {flag_2=1;}
  if(abs(current_3)!=abs(target_3)    &&   abs(current_3-target_3)>1)
  {stepper(1,stepper_delay,temp_rotn_direc_3,2);}
  else
  {flag_3=1;}

  
  
 
}}


int draw_line( double x1, double y1, double x2, double y2)
{ double slope=0;
  
   {slope=(y2-y1)/(x2-x1);}
  Serial.println(slope);
  if(slope>=1)
  {for(double i=0; i<abs(y2-y1); i=i+0.1)
  {if(y2>y1)
    {line_y[int(i*10)]=y1+i;}
   else
    {line_y[int(i*10)]=y1-i;}
  line_x[int(i*10)]=((1/slope)*(line_y[int(i*10)]-y1))+x1;
  //Serial.print(line_x[i*10]);Serial.print("        ");Serial.println(line_y[i*10]);
  goto_func(line_x[int(i*10)],line_y[int(i*10)]);}
  }
  
  else
  {for(double i=0; i<abs(x2-x1); i=i+0.1)
  {if(x2>x1)
    {line_x[int(i*10)]=x1+i;}
   else
    {line_x[int(i*10)]=x1-i;}
  line_y[int(i*10)]=((slope)*(line_x[int(i*10)]-x1))+y1;
  //Serial.print(line_x[i*10]);Serial.print("        ");Serial.println(line_y[i]*10);
  goto_func(line_x[int(i*10)],line_y[int(i*10)]);}
  } 
} 


double enc_steps(int cp,int ip,double s)
{ flag_1=0;
  if(cp>ip+2  ||  cp+2<ip  )
  {digitalWrite(13,HIGH);
    if(cp>ip)
    {   if(cp>ip+800)
             {s=s-(ip+1+982-cp);}
        else
      {s=s+(cp-ip);}
      }

   if(cp<ip)
    {   if(cp+800<ip)
             {s=s+(cp+1+982-ip);}
        else
              {s=s-(ip-cp);}
              }
//Serial.println(s);
    //delay(1);
  
flag_1=1;
  }
   return(s);
   
}

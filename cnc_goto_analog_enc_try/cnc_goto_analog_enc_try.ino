const int stepPin_2 = 10; 
const int dirPin_2= 11; 

const int stepPin_1 = 8;                          //8
const int dirPin_1= 9;                              //9

const int stepPin_3 = 6;                          //8
const int dirPin_3= 7;

int temp4=0;

double current_1_enc=0;
int enc_1=0;
int initial_pos_1=0;
int current_pos_1=0;
double steps_1=0;
double enc_steps(int,int,int);
int flag_1=0;


double current_2_enc=0;
int enc_2=3;
int initial_pos_2=0;
int current_pos_2=0;
double steps_2=0;
int flag_2=0;



 
const int led_Pin=13;
int stepper(int, int, int, int);           // steps  speed  direction   motor

double current_1=0;
double current_2=0;
double current_3=0;

double theta1=0, theta2=0, theta3=0;

double line_x;
double line_y;




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
  pinMode(enc_2,INPUT);
  initial_pos_2=analogRead(enc_2);
  
int m=0;


Serial.begin(9600);
//stepper(1,1000,0,0);
//stepper(1,1000,0,1);
digitalWrite(led_Pin,LOW);
noInterrupts();           // disable all interrupts

  TCCR1A = 0;

  TCCR1B = 0;

  TCNT1  = 0;


  OCR1A = 31250/4;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler 

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();             // enable all interrupts



}



void loop() {
double temp_steps=200*56/15;
//digitalWrite(led_Pin,HIGH);
if(Serial.available()>0)
{char s='p';
s=Serial.read();
if(s=='q')
{for( int i=0; i<(200*56/15); i++)
{stepper(1,400,0,0);
stepper(1,400,1,1);
//digitalWrite(led_Pin,HIGH);
}
s='p';

}

if(s=='r')
{for( int i=0; i<temp_steps; i++)
{stepper(1,400,1,0);
stepper(1,400,0,1);
//digitalWrite(led_Pin,HIGH);
}
s='p';

}

if(s=='s')
{for( int i=0; i<temp_steps; i++)
 {stepper(1,1000,1,1);
//digitalWrite(led_Pin,HIGH);
}
s='p';
}

if(s=='d')
{for( int i=0; i<temp_steps; i++)
  {stepper(1,1000,0,1);
//digitalWrite(led_Pin,HIGH);
}
s='p';
}


if(s=='z')
{for( int i=0; i<temp_steps; i++)
 {stepper(1,950,1,2);
//digitalWrite(led_Pin,HIGH);
}
s='p';}

if(s=='x')
{for( int i=0; i<temp_steps; i++)
  {stepper(1,950,0,2);
//digitalWrite(led_Pin,HIGH);
}
s='p';}


if(s=='m')
{goto_func(-20,0);Serial.print(current_1_enc);Serial.print("        ");Serial.print(current_2_enc);Serial.print("        ");Serial.println(temp4);
s='p';}

if(s=='n')
{goto_func(0,0);Serial.print(current_1_enc);Serial.print("        ");Serial.println(current_2_enc);Serial.println("        ");
s='p';}

if(s=='f')
{goto_func(-100,0);
s='p';}

if(s=='l')
{//draw_line(0,0,0,75);
  draw_line(0,0,-25,0);
s='p';
}

if(s=='c')
{draw_circle(0,0,10);
//draw_circle(0,0,20);
//draw_circle(0,0,30);
//draw_circle(0,0,40);
s='p';
}

if(s=='v')
{Serial.print(steps_1);Serial.print("   ");Serial.println(steps_2);
s='p';}


if(s=='b')
{draw_circle(0,0,16);
//goto_func(90,0);
draw_circle(90,0,3);
//goto_func(100,0);
draw_line(100,0,100,25);
draw_line(100,25,-100,25);
draw_line(-100,25,-100,-25);
draw_circle(-90,0,3);
draw_line(-100,-25,100,-25);
draw_line(100,-25,100,0);
s='p';
}


}
 
/*stepper(97,3000,1);
delay(3000);
stepper(97,3000,0);
delay(3000);*/

//stepper(97,800,0,0);
//stepper(97,800,0,1);
//Serial.print(steps_1);Serial.print("       ");Serial.println(steps_2);
//Serial.print(current_1/15.08888);Serial.print("          ");Serial.println(current_2/15.088888);



}



int stepper( int steps, int rpm, int rotn_direc, int motor)
{int m=0;
digitalWrite(dirPin_1,rotn_direc);
digitalWrite(dirPin_2,rotn_direc);
digitalWrite(dirPin_3,rotn_direc);

int temp=89;




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


current_1_enc=steps_1*200*56/15/998*0.9875;                //change 982 value
//Serial.print(steps_1);Serial.print("        ");




current_2_enc=steps_2*200*56/15/987*0.9875;                       //change 982 value
//Serial.println(steps_2);
//Serial.print(current_1);Serial.print("  ");Serial.println(current_2);
//Serial.println(temp);

while(m<steps)
{   digitalWrite(temp,HIGH);
    delayMicroseconds(rpm);
    digitalWrite(temp,LOW);
    delayMicroseconds(rpm);
  m++;
  }
}





int goto_func(double x , double y)

{
 
double target_1=x*200/1.25*56/15;
double target_2=x*200/1.25*56/15;
double target_3=y*200/1.25*56/15;

//Serial.println(target_1);Serial.println(target_3);

int temp_rotn_direc_1=0;
int temp_rotn_direc_2=1;
int temp_rotn_direc_3=1;





int flag_1=0, flag_2=0, flag_3=0, flag=0;
while(1)
{//Serial.println(abs(target_2-current_2));

  

   
  if(abs(current_1-current_1_enc)>50)
  {current_1=current_1_enc;temp4++;
  }

  if(abs(current_2-current_2_enc)>50)
  {current_2=current_2_enc;temp4++;
  }

   temp_rotn_direc_1=0;
 temp_rotn_direc_2=1;
 temp_rotn_direc_3=1;

if( target_1-current_1>=0  )
{temp_rotn_direc_1=1;}                              //change to proper val
if( target_2-current_2>0)
{temp_rotn_direc_2=0;}
if( target_3-current_3>0)
{temp_rotn_direc_3=0;}


  
  if(flag_1==1    &&    flag_2==1   &&   flag_3==1)
  {break;}
  
  flag=flag_1+flag_2+flag_3;
  int stepper_delay=800/(3-flag);
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
} 


int draw_circle( double cx, double cy, double r)
{double circle_x=0, circle_y=0;digitalWrite(13,HIGH);
circle_x=cx*(1+(r*cos(0)));circle_y=cy*(1+(r*sin(0)));
for( double i=0; i<=360; i=i+0.5)
{circle_x=cx+(r*cos(i*3.14159/180));
circle_y=cy+(r*sin(i*3.14159/180));
//Serial.print(circle_x);Serial.print("     ");Serial.println(circle_y);
goto_func(circle_x,circle_y);
}
}

double enc_steps(int cp,int ip,double s,int l)
{ int ref_vol;
  if(l=0)
  {ref_vol=960;}
  else
  {ref_vol=1004;}
  if(cp>ip+2  ||  cp+2<ip  )
  {//digitalWrite(13,HIGH);
    if(cp>ip)
    {   if(cp>ip+800)
             {s=s-(ip+1+ref_vol-cp);}
        else
      {s=s+(cp-ip);}
      }
   if(cp<ip)
    {   if(cp+800<ip)
             {s=s+(cp+1+ref_vol-ip);}
        else
              {s=s-(ip-cp);}
              }   
  }
   return(s);
}



ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine

{

  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
current_pos_1=analogRead(enc_1);
steps_1=enc_steps(current_pos_1,initial_pos_1,steps_1,0);{  initial_pos_1=current_pos_1;}//Serial.print(steps_1);Serial.print("          ");


current_pos_2=analogRead(enc_2);
steps_2=enc_steps(current_pos_2,initial_pos_2,steps_2,1);{  initial_pos_2=current_pos_2;}//Serial.print(steps_2);Serial.print("          ");Serial.print(target_1);Serial.print("          ");Serial.println(target_2);
}

const int stepPin_2 = 10; 
const int dirPin_2= 11; 


const int stepPin_1 = 8; 
const int dirPin_1= 9; 

const int led_Pin=13;
int stepper(int, int, int, int);           // steps  speed  direction   motor

double current_1=0;
double current_2=0;

double theta1=0, theta2=0;

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin_1,OUTPUT); 
  pinMode(dirPin_1,OUTPUT);
  pinMode(stepPin_2,OUTPUT); 
  pinMode(dirPin_2,OUTPUT);
  pinMode(led_Pin,OUTPUT);
int m=0;
Serial.begin(9600);
stepper(1,1000,0,0);
stepper(1,1000,0,1);
inv_kinematics(300,0);
int steps_1=theta1*679/45;
int steps_2=theta2*679/45;


int temp_rotn_direc_1=0;
int temp_rotn_direc_2=1;
if( steps_1>0)
{temp_rotn_direc_1=1;}                              //change to proper val
if( steps_2>0)
{temp_rotn_direc_2=0;}
int flag_1=0, flag_2=0;
while(1)
{
  if((current_1)!=(steps_1))
  {stepper(1,500,temp_rotn_direc_1,0);}
  else
  {flag_1=1;}
 if(abs(current_2)!=abs(steps_2))
  {stepper(1,500,temp_rotn_direc_2,1);}
  else
  {flag_2=1;}
  if(flag_1==1    &&    flag_2==1)
  {break;}
}
}



void loop() {
int temp_steps=679/9;
digitalWrite(led_Pin,LOW);
if(Serial.available()>0)
{char s='p';
s=Serial.read();
if(s=='q')
{for( int i=0; i<temp_steps; i++)
{stepper(1,1500,0,0);
digitalWrite(led_Pin,HIGH);}
s='p';
}

if(s=='r')
{for( int i=0; i<temp_steps; i++)
{stepper(1,1500,1,0);
digitalWrite(led_Pin,HIGH);}
s='p';
}

if(s=='s')
{for( int i=0; i<temp_steps; i++)
 {stepper(1,1500,1,1);
digitalWrite(led_Pin,HIGH);}
s='p';}

if(s=='d')
{for( int i=0; i<temp_steps; i++)
  {stepper(1,1500,0,1);
digitalWrite(led_Pin,HIGH);}
s='p';}



} 
/*stepper(97,3000,1);
delay(3000);
stepper(97,3000,0);
delay(3000);*/

//stepper(97,800,0,0);
//stepper(97,800,0,1);

//Serial.print(current_1/15.08888);Serial.print("          ");Serial.println(current_2/15.088888);
}


int stepper( int steps, int rpm, int rotn_direc, int motor)
{int m=0;
digitalWrite(dirPin_1,rotn_direc);
digitalWrite(dirPin_2,rotn_direc);
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
Serial.print(current_1*45/679);Serial.print("       ");Serial.println(current_2*45/679);
//Serial.println(temp);

while(m<steps)
{   digitalWrite(temp,HIGH);
    delayMicroseconds(rpm);
    digitalWrite(temp,LOW);
    delayMicroseconds(rpm);
  m++;
  }

}


int inv_kinematics(double x1, double y1)
{  
 theta2=(acos(((x1*x1)+(y1*y1)-72148)/32376/2));
 theta1=(atan2(y1,x1)-atan2(228*sin(theta2),(142+(228*cos(theta2)))));         //getting values of joint angles
theta2=theta2*180/3.142;    theta1=theta1*180/3.142;
Serial.print(theta1);Serial.print("      ");Serial.println(theta2);
}

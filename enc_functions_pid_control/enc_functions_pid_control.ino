int enc0=2;
int initial_pos0=0;
int current_pos0=0;
int steps0=0;
int kp=4.5, ki=0.170, kd=2.5;
boolean a=LOW,b=LOW;int pwmval=0;
int flag=0;     int target=0000;
int pidfunc(int,int,int);
int enc_steps(int,int,int);
int motor_clockwise=11;
int motor_anticlockwise=12;
int motor_pwm=7;


void setup() {
  // put your setup code here, to run once:
pinMode(enc0,INPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);
initial_pos0=analogRead(enc0);
}



void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0);
{ char n=Serial.read();
if(n=='s')
{target=target+15;}
if(n=='r')
{target=target-15;}
}
current_pos0=analogRead(enc0);
digitalWrite(13,LOW);
steps0=enc_steps(current_pos0,initial_pos0,steps0);if(flag==1){  initial_pos0=current_pos0;}
pwmval=pidfunc(steps0,target,pwmval);
Serial.print(steps0);Serial.print("      ");Serial.println(target);
digitalWrite(motor_clockwise,a);
digitalWrite(motor_anticlockwise,b);
analogWrite(motor_pwm,pwmval);



    
 

  
}

int enc_steps(int cp,int ip,int s)
{ flag=0;

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
    delay(1);
  
    flag=1;

   
   
 

  }
   return(s);
}


int pidfunc(int currentvalue,int targetvalue,int pwmvalue)

 {
   pwmvalue=0;
    int error=targetvalue-currentvalue;static int lasterror=0;static int totalerror=0;
    float pidterm=0;
    if(currentvalue==targetvalue && targetvalue==pwmvalue)
      { lasterror=0;totalerror=0;}
    
     
     if(error>0)
    {a=HIGH;b=LOW;}
    else
    {a=LOW;b=HIGH;}
   
    
    totalerror=totalerror+error;
    pidterm=kp*(error)+ki*(totalerror)+kd*(error-lasterror);
    lasterror=error;pidterm=abs(pidterm);
    //Serial.println(pidterm);
   
    return(constrain((pwmvalue+pidterm),0,150));
   
   }



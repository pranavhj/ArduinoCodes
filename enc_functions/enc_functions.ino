int enc0=3;
int initial_pos0=0;
int current_pos0=0;
int steps0=0;
int enc_steps(int,int,int);
int flag=0;
void setup() {
  // put your setup code here, to run once:
pinMode(enc0,INPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);
initial_pos0=analogRead(enc0);
}

void loop() {
  // put your main code here, to run repeatedly:

current_pos0=analogRead(enc0);//Serial.println(current_pos0);
digitalWrite(13,LOW);
steps0=enc_steps(current_pos0,initial_pos0,steps0);if(flag==1){  initial_pos0=current_pos0;}


    
 

  
}

int enc_steps(int cp,int ip,int s)
{ flag=0;

  if(cp>ip+2  ||  cp+2<ip  )
  {digitalWrite(13,HIGH);
    if(cp>ip)
    {   if(cp>ip+800)
             {s=s-(ip+1+1004-cp);}
        else
      {s=s+(cp-ip);}
      }

   if(cp<ip)
    {   if(cp+800<ip)
             {s=s+(cp+1+1004-ip);}
        else
              {s=s-(ip-cp);}
              }
    
    
   
    Serial.println(s);
    delay(1);
  
    flag=1;

   
   
 

  }
   return(s);
}

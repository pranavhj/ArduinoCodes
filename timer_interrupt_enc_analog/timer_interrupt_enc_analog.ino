#define ledPin 13
int enc_1=0;
int enc_2=3; 



int initial_pos_1=0;
int current_pos_1=0;
float steps_1=0;                                //steps func intitialization for 1st enc
int enc_steps_1(int,int,float,int);

int initial_pos_2=0;
int current_pos_2=0;                            //steps func intitialization for 2nd enc
float steps_2=0;


void setup()

{pinMode(enc_1,INPUT);
pinMode(enc_2,INPUT);
initial_pos_1=analogRead(enc_1);
initial_pos_2=analogRead(enc_2);

Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  

  // initialize timer1 

  noInterrupts();           // disable all interrupts

  TCCR1A = 0;

  TCCR1B = 0;

  TCNT1  = 0;


  OCR1A = 31250/2;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler 

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();             // enable all interrupts

}


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine

{

  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
current_pos_1=analogRead(enc_1);
steps_1=enc_steps(current_pos_1,initial_pos_1,steps_1,0);{  initial_pos_1=current_pos_1;}//Serial.print(steps_1);Serial.print("          ");


current_pos_2=analogRead(enc_2);
steps_2=enc_steps(current_pos_2,initial_pos_2,steps_2,1);{  initial_pos_2=current_pos_2;}//Serial.print(steps_2);Serial.print("          ");Serial.print(target_1);Serial.print("          ");Serial.println(target_2);
}


void loop()

{
Serial.print(steps_1);Serial.print("          ");Serial.println(steps_2);
  

}

int enc_steps(int cp,int ip,float s,int l)
{   int ref_vol;
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

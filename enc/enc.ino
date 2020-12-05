int enc=0;
int initial_pos=0;
int current_pos=0;
int steps=0;

void setup() {
  // put your setup code here, to run once:
pinMode(enc,INPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);
initial_pos=analogRead(enc);
}

void loop() {
  // put your main code here, to run repeatedly:

current_pos=analogRead(enc);
//Serial.println(current_pos);
digitalWrite(13,LOW);


if(current_pos>initial_pos+3  ||  current_pos+3<initial_pos  )
  {if(current_pos>initial_pos)
    {   if(current_pos>initial_pos+800)
             {steps=steps-(initial_pos+1+982-current_pos);}
        else
      {steps=steps+(current_pos-initial_pos);}
      }

   if(current_pos<initial_pos)
    {   if(current_pos+800<initial_pos)
             {steps=steps+(current_pos+1+982-initial_pos);}
        else
              {steps=steps-(initial_pos-current_pos);}
              }
    
    
    
    initial_pos=current_pos;
    Serial.println(steps);
    delay(1);
    digitalWrite(13,HIGH);
    
 

  }
}


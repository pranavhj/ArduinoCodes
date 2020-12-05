//Coded By: Angelo Casimiro (4/27/14)
//Voice Activated Arduino (Bluetooth + Android)
//Feel free to modify it but remember to give credit
#include <SoftwareSerial.h>

SoftwareSerial BT(11, 10); //TX, RX respetively       
String voice;
int ledpin=12;
void setup() {
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(ledpin, OUTPUT); 

}
//-----------------------------------------------------------------------//  
void loop() {
  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = BT.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  }  
  if (voice.length() > 0) {
    Serial.println(voice); 

  if(voice == "*start") 
  {
    digitalWrite(ledpin, HIGH);
  } 
  
  else if(voice == "*stop") 
  {
    digitalWrite(ledpin, LOW);
  }
    else (voice == "*hi") ;
    {
   for(ledpin=0;ledpin<10;ledpin++)
   {digitalWrite(ledpin, LOW);delay(200); digitalWrite(ledpin, HIGH);delay(200);
  }}
  
   

voice="";}} //Reset the variable after initiating

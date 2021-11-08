#include "RF24.h"


RF24 myControl (7, 8); 
byte addresses[][6] = {"0"}; 
int potmeterVol = A0;
int potmeterTreb = A1;
int potmeterMid = A2;
int potmeterBass = A3;
int volume = 0;
int treble = 0;
int mid = 0;
int bass = 0;

struct package
{
  int id=1;
  int volume = 0;
  int treble = 0;
  int mid = 0;
  int bass = 0;
};
typedef struct package Package;
Package data;

void setup()
{
  myControl.begin();  
  myControl.setChannel(115); 
  myControl.setPALevel(RF24_PA_MIN);
  myControl.setDataRate( RF24_250KBPS ) ; 
  myControl.openWritingPipe( addresses[0]);
}

void loop()
{
  readPot();
  myControl.write(&data, sizeof(data)); 
} 

void readPot(){
  data.volume = analogRead(potmeterVol); // Lee el dato y el resultado lo manda directo al paquete de envío
  data.treble = analogRead(potmeterTreb);
  data.mid = analogRead(potmeterMid);
  data.bass = analogRead(potmeterBass);
}


 

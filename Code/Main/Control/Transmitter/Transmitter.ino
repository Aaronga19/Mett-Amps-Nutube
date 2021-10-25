#include "RF24.h"


RF24 myControl (7, 8); 
byte addresses[][6] = {"0"}; 
int potmeterPin1 = A0;
int potmeterPin2 = A1;
int potmeterPin3 = A2;
int potmeterPin4 = A3;
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

  char  text[100] = "Text to be transmitted";
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
  data.volume = analogRead(potmeterPin1); // Lee el dato y el resultado lo manda directo al paquete de envío
  data.treble = analogRead(potmeterPin2);
  data.mid = analogRead(potmeterPin3);
  data.bass = analogRead(potmeterPin4);
}


 

#include "RF24.h"


RF24 monControle (7, 8); 
byte addresses[][6] = {"0"}; 
int potmeterPin1 = A0;
int potmeterPin2 = A1;
int potmeterPin3 = A2;
int potmeterPin4 = A3;
int volume = 0;
int tripler = 0;
int milieu = 0;
int bas = 0;

struct package
{
  int id=1;
  int volume = 0;
  int tripler = 0;
  int milieu = 0;
  int bas = 0;

  char  text[100] = "Text to be transmitted";
};
typedef struct package Package;
Package data;

void setup()
{
  Serial.begin(115200);
  delay(100);
  monControle.begin();  
  monControle.setChannel(115); 
  monControle.setPALevel(RF24_PA_MIN);
  monControle.setDataRate( RF24_250KBPS ) ; 
  monControle.openWritingPipe( addresses[0]);
}

void loop()
{
  lirePot();
  monControle.write(&data, sizeof(data)); 
  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.print("Volume: ");
  Serial.println(data.volume);
  Serial.print("Treble: ");
  Serial.println(data.tripler);
  Serial.print("Mid: ");
  Serial.println(data.milieu);
  Serial.print("Bass: ");
  Serial.println(data.bas);
  Serial.println(data.text);
  data.id = data.id + 1;;
  delay(100);
} 

void lirePot(){
  data.volume = analogRead(potmeterPin1); // Lee el dato y el resultado lo manda directo al paquete de envío
  data.tripler = analogRead(potmeterPin2);
  data.milieu = analogRead(potmeterPin3);
  data.bas = analogRead(potmeterPin4);
  //Serial.print(potmeterVal);
  //Serial.print("\n");
}


 

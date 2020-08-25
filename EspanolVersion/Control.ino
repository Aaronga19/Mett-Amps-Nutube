#include "RF24.h"


RF24 miControl (7, 8); 
byte addresses[][6] = {"0"}; 
int potmeterPin1 = A0;
int potmeterPin2 = A1;
int potmeterPin3 = A2;
int potmeterPin4 = A3;
int volume = 0;
int agud = 0;
int med = 0;
int baj = 0;

struct package
{
  int id=1;
  int volume = 0;
  int agud = 0;
  int med = 0;
  int baj = 0;

  char  text[100] = "Text to be transmitted";
};
typedef struct package Package;
Package data;

void setup()
{
  Serial.begin(115200);
  delay(100);
  miControl.begin();  
  miControl.setChannel(115); 
  miControl.setPALevel(RF24_PA_HIGH);
  miControl.setDataRate( RF24_250KBPS ) ; 
  miControl.openWritingPipe( addresses[0]);
}
void leerPot(){
  data.volume = analogRead(potmeterPin1); // Lee el dato y el resultado lo manda directo al paquete de envío
  data.agud = analogRead(potmeterPin2);
  data.med = analogRead(potmeterPin3);
  data.baj = analogRead(potmeterPin4);
  //Serial.print(potmeterVal);
  //Serial.print("\n");
}
void loop()
{
  leerPot();
  miControl.write(&data, sizeof(data)); 
  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.print("Volume: ");
  Serial.println(data.volume);
  Serial.print("Treble: ");
  Serial.println(data.agud);
  Serial.print("Mid: ");
  Serial.println(data.med);
  Serial.print("Bass: ");
  Serial.println(data.baj);
  Serial.println(data.text);
  data.id = data.id + 1;;
  delay(100);
} 

#include "RF24.h"
#include <LiquidCrystal.h>
#include <DigiPotX9Cxxx.h>

DigiPot PotVol(10,A0,A1); // INC, U/D, CS
/*DigiPot PotBass(10,A0,A1); // INC, U/D, CS
DigiPot PotMid(10,A0,A1); // INC, U/D, CS
DigiPot PotTreb(10,A0,A1); // INC, U/D, CS
*/
LiquidCrystal pantalla(6,5,4,3,2,9); // Conexión RS,E,D4,D5,D6,D7
RF24 myAmp (7, 8); // in Mega can use> (48, 49); 
byte addresses[][6] = {"0"}; 
int resistencia = 0;

struct package
{
  int id=0;
  int volume = 0;
  int tripler = 0;
  int milieu = 0;
  int bas = 0;

  char  text[100] ="empty";
};
typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(70);
  pantalla.begin(16,2);
  myAmp.begin(); 
  myAmp.setChannel(115); 
  myAmp.setPALevel(RF24_PA_HIGH);
  myAmp.setDataRate( RF24_250KBPS ) ; 
  myAmp.openReadingPipe(1, addresses[0]);
  myAmp.startListening();
}

void loop()  
{
  if ( myAmp.available()) 
  {
    while (myAmp.available())
    {
      myAmp.read( &data, sizeof(data) );
    }
    pantalla.clear();
    pantalla.setCursor(0,0);
    pantalla.print("Pack");
    pantalla.setCursor(5,0);
    pantalla.print(data.id);
                            //Organizacion de lcd para Volume
    int volumen = map(data.volume,0, 1023, 0, 99);
    pantalla.setCursor(10,0);
    pantalla.print("Vol ");
    pantalla.setCursor(14,0);
    pantalla.print(volumen);
    PotVol.set(volumen);
                            // Organización de lcd para Treble
    int bajos = map(data.bas,0, 1023, 0, 99);
    pantalla.setCursor(0,1);
    pantalla.print("Ba ");
    pantalla.setCursor(3,1);
    pantalla.print(bajos);
                             // Organización de lcd para Middle
    int medios = map(data.milieu,0, 1023, 0, 99);                       
    pantalla.setCursor(5,1);
    pantalla.print("Me");
    pantalla.setCursor(8,1);
    pantalla.print(medios);
                             // Organización de lcd para Bass
    int agudos = map(data.tripler,0, 1023, 0, 99);   
    pantalla.setCursor(10,1);
    pantalla.print("Agu");
    pantalla.setCursor(14,1);
    pantalla.print(agudos);
                            // Monitoreo por puerto serial
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.print("Volumen: ");
    Serial.println(data.volume);
    Serial.print("Treb: ");
    Serial.println(data.tripler);
    Serial.print("Mid: ");
    Serial.println(data.milieu);
    Serial.print("Bass: ");
    Serial.println(data.bas);
    Serial.println(data.text);
  }
  /*else
  pantalla.setCursor(1,0);
  pantalla.print("Controller off");
  pantalla.setCursor(1,1);
  pantalla.print("Please turn on");*/
}

#include "RF24.h"
#include <LiquidCrystal.h>
#include <DigiPotX9Cxxx.h>

DigiPot PotVol(2,A0,A1); // INC, U/D, CS
DigiPot PotBaj(3,A2,A3); // INC, U/D, CS
DigiPot PotMed(4,A4,A5); // INC, U/D, CS
DigiPot PotAgud(5,A6,A7); // INC, U/D, CS

LiquidCrystal pantalla(44,45,42,43,40,41); // Conexión: RS,E,D4,D5,D6,D7 

RF24 miAmp (48, 49); // Conexión: (CE,CSN) SCK->52, MOSI->51, MISO->50
byte addresses[][6] = {"0"}; 


struct package
{
  int id=0;
  int volume = 0;
  int agud = 0;
  int med = 0;
  int baj = 0;
  char  text[100] ="vacio";
};
typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(100);
  pantalla.begin(16,2);
  miAmp.begin(); 
  miAmp.setChannel(115); 
  miAmp.setPALevel(RF24_PA_HIGH);
  miAmp.setDataRate( RF24_250KBPS ) ; 
  miAmp.openReadingPipe(1, addresses[0]);
  miAmp.startListening();
}

void loop()  
{
  if ( miAmp.available()) 
  {
    while (miAmp.available())
    {
      miAmp.read(&data, sizeof(data));
    }
    pantalla.clear();
    pantalla.setCursor(0,0);
    pantalla.print("Pack");
    pantalla.setCursor(5,0);
    pantalla.print(data.id);
                            //Organizacion de lcd para Volume
    int volumen = map(data.volume,0, 1023, 0, 100);
    pantalla.setCursor(10,0);
    pantalla.print("Vol ");
    pantalla.setCursor(14,0);
    pantalla.print(volumen);
    PotVol.set(volumen);
                            // Organización de lcd para Treble
    int bajos = map(data.baj,0, 1023, 0, 100);
    pantalla.setCursor(0,1);
    pantalla.print("Ba ");
    pantalla.setCursor(3,1);
    pantalla.print(bajos);
    PotBaj.set(bajos);
                             // Organización de lcd para Middle
    int medios = map(data.med,0, 1023, 0, 100);                       
    pantalla.setCursor(5,1);
    pantalla.print("Me");
    pantalla.setCursor(8,1);
    pantalla.print(medios);
    PotMed.set(medios);

                             // Organización de lcd para Bass
    int agudos = map(data.agud,0, 1023, 0, 100);   
    pantalla.setCursor(10,1);
    pantalla.print("Agu");
    pantalla.setCursor(14,1);
    pantalla.print(agudos);
    PotAgud.set(agudos);
                            // Monitoreo por puerto serial
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.print("Volumen: ");
    Serial.println(data.volume);
    Serial.print("Treb: ");
    Serial.println(data.agud);
    Serial.print("Mid: ");
    Serial.println(data.medi);
    Serial.print("Bass: ");
    Serial.println(data.baj);
    Serial.println(data.text);
  }
  /*else
  pantalla.setCursor(1,0);
  pantalla.print("Controller off");
  pantalla.setCursor(1,1);
  pantalla.print("Please turn on");*/
}

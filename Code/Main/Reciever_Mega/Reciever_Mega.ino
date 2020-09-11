#include "RF24.h"
#include <LiquidCrystal.h>
#include <DigiPotX9Cxxx.h>

DigiPot PotVol(2,A0,A1); // INC, U/D, CS
DigiPot PotBas(3,A2,A3); // INC, U/D, CS
DigiPot PotMilieu(4,A4,A5); // INC, U/D, CS
DigiPot PotTripler(5,A6,A7); // INC, U/D, CS
LiquidCrystal pantalla(44,45,42,43,40,41); // Conexión: RS,E,D4,D5,D6,D7 
RF24 myAmp (48, 49); // Conexión: (CE,CSN) SCK->52, MOSI->51, MISO->50
byte addresses[][6] = {"0"}; 

int Li = 16;
int Lii = 0;


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
delay(100);
pinMode(22, INPUT);
pantalla.begin(16,2);
myAmp.begin(); 
myAmp.setChannel(115); 
myAmp.setPALevel(RF24_PA_MIN);
myAmp.setDataRate( RF24_250KBPS ) ; 
myAmp.openReadingPipe(1, addresses[0]);
myAmp.startListening();
}

void loop(){
pantalla.clear();
pantalla.setCursor(4,0);
pantalla.print("Manual");
pantalla.setCursor(4,1);
pantalla.print("Mode");
  /*int mode = digitalRead(6);
  Serial.print(mode);
                      // HIGH = Modo Inalambrico
                      // LOW = Modo Manual
  if (mode == HIGH){
    pantalla.setCursor(4,0);
    pantalla.print("Wireless");
    pantalla.setCursor(6,1);
    pantalla.print("Mode");  
    
    if ( myAmp.available()){
      while (myAmp.available()){
        myAmp.read(&data, sizeof(data));
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
      int bajos = map(data.bas,0, 1023, 0, 100);
      pantalla.setCursor(0,1);
      pantalla.print("Ba ");
      pantalla.setCursor(3,1);
      pantalla.print(bajos);
      PotBas.set(bajos);
                             // Organización de lcd para Middle
      int medios = map(data.milieu,0, 1023, 0, 100);                       
      pantalla.setCursor(5,1);
      pantalla.print("Me");
      pantalla.setCursor(8,1);
      pantalla.print(medios);
      PotMilieu.set(medios);

                             // Organización de lcd para Bass
      int agudos = map(data.tripler,0, 1023, 0, 100);   
      pantalla.setCursor(10,1);
      pantalla.print("Agu");
      pantalla.setCursor(14,1);
      pantalla.print(agudos);
      PotTripler.set(agudos);
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
                            // Si el control esta apagado
    else {
      pantalla.clear();
      pantalla.setCursor(0,0);
      pantalla.print("   No control");
      pantalla.setCursor(0,1);
      pantalla.print(Scroll_LCD_Left("Please turn on or verify the connexion"));
      delay(250);
    }
  }
  else{
    pantalla.clear();
    pantalla.setCursor(4,0);
    pantalla.print("Manual");
    pantalla.setCursor(4,1);
    pantalla.print("Mode");
  }


*/
}



String Scroll_LCD_Left(String StrDisplay){
  String result;
  String StrProcess = "                 " + StrDisplay + "                 ";
  result = StrProcess.substring(Li,Lii);
  Li++;
  Lii++;
  if (Li > StrProcess.length()){
    Li=16;
    Lii = 0; 
  }
  return result;
}
void Clear_Scroll_LCD_Rigth(){
  Li=16;
  Lii=0;
}

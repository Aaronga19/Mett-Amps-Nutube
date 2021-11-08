#include "RF24.h"
#include <LiquidCrystal.h>
#include <DigiPotX9Cxxx.h>

DigiPot PotVol(2,A0,A1); // INC, U/D, CS
DigiPot PotBass(3,A2,A3); // INC, U/D, CS
DigiPot PotMid(4,A4,A5); // INC, U/D, CS
DigiPot PotTreble(5,A6,A7); // INC, U/D, CS
LiquidCrystal pantalla(44,45,42,43,40,41); // Connection: RS,E,D4,D5,D6,D7 
RF24 myAmp (48, 49); // Connection: (CE,CSN) SCK->52, MOSI->51, MISO->50
byte addresses[][6] = {"0"}; 

int Li = 16;
int Lii = 0;

int mode = 0;


int analogTreble = A10;
int analogMid = A9;
int analogBass = A8;
int analogVolume = A11;

struct package
{
  int id=0;
  int volume = 0;
  int treble = 0;
  int mid = 0;
  int bass = 0;
};
typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(9600);
  pinMode(6,INPUT);
  pantalla.begin(16,2);
  pantalla.clear();
  myAmp.begin(); 
  myAmp.setChannel(115); 
  myAmp.setPALevel(RF24_PA_MIN);
  myAmp.setDataRate( RF24_250KBPS ) ; 
  myAmp.openReadingPipe(1, addresses[0]);
  myAmp.startListening();
 
}

void loop()  
{
  ReadMode(500);
                                // Cuando se coloca en modo inalambrico
  while (mode == HIGH){
    if (mode == HIGH){
          WirelessMode();
          ControlOff();
    }                           // En caso de que el control este prendido
    while (mode == HIGH){
      ReadMode(1);
      
      while(myAmp.available()==false) {
          Serial.print("My amp: ");
          Serial.println(myAmp.available());
          pantalla.clear();
          pantalla.setCursor(0,0);
          pantalla.print("**Control Off**");
          pantalla.setCursor(0,1);
          pantalla.print(Scroll_LCD_Left("Turn on or verify the connection"));
          delay(250);
      }
      
      while (myAmp.available()){
        pantalla.clear();
        myAmp.read(&data, sizeof(data));

                                //Organizacion de lcd para Volume
        int volumen = map(data.volume,0, 1023, 0, 100);
        pantalla.setCursor(2,0);
        pantalla.print("Volumen: ");
        pantalla.setCursor(12,0);
        pantalla.print(volumen);
        PotVol.set(volumen);
                                // Organización de lcd para Treble
        int bajos = map(data.bass,0, 1023, 0, 100);
        pantalla.setCursor(0,1);
        pantalla.print("Ba ");
        pantalla.setCursor(3,1);
        pantalla.print(bajos);
        PotBass.set(bajos);
                                // Organización de lcd para Middle
        int medios = map(data.mid,0, 1023, 0, 100);                       
        pantalla.setCursor(5,1);
        pantalla.print("Me");
        pantalla.setCursor(8,1);
        pantalla.print(medios);
        PotMid.set(medios);
    
                                // Organización de lcd para Bass
        int agudos = map(data.treble,0, 1023, 0, 100);   
        pantalla.setCursor(10,1);
        pantalla.print("Agu");
        pantalla.setCursor(14,1);
        pantalla.print(agudos);
        PotTreble.set(agudos);

       }
    }                          
      
  }

  /*=============================================================*/
  
                                // Cuando se coloca en modo Manual
    while (mode == LOW){
      if (mode == LOW){
          ManualMode();
        }
      pantalla.clear();
      while(mode == LOW){
        ReadMode(1);
        analogVolume = analogRead(A11);
        delay(50);
                                // Modificar el volumen con potenciometro
        int volumen = map(analogVolume,0, 1022, 0, 100);
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Volumen: ");
        pantalla.setCursor(12,0);
        pantalla.print(volumen);
        PotVol.set(volumen);

        analogBass = analogRead(A8);    
        int bajos = map(analogBass,0, 1022, 0, 100);
        pantalla.setCursor(0,1);
        pantalla.print("Ba ");
        pantalla.setCursor(3,1);
        pantalla.print(bajos);
        PotBass.set(bajos);

        analogMid = analogRead(A9);
        int medios = map(analogMid,0, 1022, 0, 100);                       
        pantalla.setCursor(5,1);
        pantalla.print("Me");
        pantalla.setCursor(8,1);
        pantalla.print(medios);
        PotMid.set(medios);

        analogTreble = analogRead(A10);  
        int agudos = map(analogTreble,0, 1022, 0, 100);
        pantalla.setCursor(10,1);
        pantalla.print("Agu");
        pantalla.setCursor(14,1);
        pantalla.print(agudos);
        PotTreble.set(agudos); 
        }
    }
    
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

void ManualMode(){
  pantalla.clear();
  pantalla.setCursor(1,0);
  pantalla.print("Modo:"),
  pantalla.setCursor(7,1);
  pantalla.print("Manual");
  delay(3000);
  }
  
void WirelessMode(){
  pantalla.clear();
    pantalla.setCursor(1,0);
    pantalla.print("Mode:"),
    pantalla.setCursor(6,1);
    pantalla.print("Wireless");
    delay(3000);
  }

void ReadMode(int timedelay){
  mode = digitalRead(6);
  delay(timedelay);
}

void ControlOff(){
  Serial.print("My amp: ");
  Serial.println(myAmp.available());
  int timelimit = 0;
  pantalla.clear();
  pantalla.setCursor(0,0);
  pantalla.print("**Control Off**");
  pantalla.setCursor(3,1);
  pantalla.print("Turn it on");
}

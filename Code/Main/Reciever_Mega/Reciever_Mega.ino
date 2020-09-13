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

int mode = 0;


int analogTripler = A10;
int analogMilieu = A9;
int analogBas = A8;
int analogVolume = A11;

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
  Serial.begin(9600);
  delay(100);
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
  mode = digitalRead(6);
  Serial.print(mode);
                                // Cuando se coloca en modo inalambrico
  if (mode == HIGH){
    WirelessMode();
    
    while (mode == HIGH){

      if ( myAmp.available()) 
      {
        while (myAmp.available())
        {
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
        pantalla.print("**Control Off**");
        pantalla.setCursor(0,1);
        pantalla.print(Scroll_LCD_Left("Por favor enciendalo o verifique la conexion"));
        delay(250);
      }
    }
  }
                                // Cuando se coloca en modo Manual
    if (mode == LOW){
      ManualMode();
      pantalla.clear();
      while(mode == LOW){
        analogVolume = analogRead(A11);
        Serial.print("Analogico: ");
        Serial.println(analogVolume);  
                                // Modificar el volumen con potenciometro
        int volumen = map(analogVolume,0, 1022, 0, 100);
        pantalla.clear();
        pantalla.setCursor(2,0);
        pantalla.print("Volumen: ");
        pantalla.setCursor(12,0);
        pantalla.print(volumen);
        PotVol.set(volumen);

        analogBas = analogRead(A8);
        
        int bajos = map(analogBas,0, 1022, 0, 100);
        pantalla.setCursor(0,1);
        pantalla.print("Ba ");
        pantalla.setCursor(3,1);
        pantalla.print(bajos);
        PotBas.set(bajos);

        analogMilieu = analogRead(A9);

        int medios = map(analogMilieu,0, 1022, 0, 100);                       
        pantalla.setCursor(5,1);
        pantalla.print("Me");
        pantalla.setCursor(8,1);
        pantalla.print(medios);
        PotMilieu.set(medios);

        analogTripler = analogRead(A10);  
                                // Modificar el volumen con potenciometro
        int agudos = map(analogTripler,0, 1022, 0, 100);
        
        pantalla.setCursor(10,1);
        pantalla.print("Agu");
        pantalla.setCursor(14,1);
        pantalla.print(agudos);
        PotTripler.set(agudos);
        
        Serial.print("Mapeado: ");
        Serial.println(agudos);
   
        
        /*pantalla.clear();
        pantalla.setCursor(0,1);
        pantalla.print(Scroll_LCD_Left("Estamos en el while"));
        delay(250); */
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

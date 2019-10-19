#include <Keypad.h>
#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor



//Para teclado////////////////////////////
const byte Filas=4;
const byte Columnas=4;
char Tecla;
int  contador = 1;    // cuenta el nivel del menu en el que se esta
int pasajeros = 0;
char pfinal = ' ';
char paraderos[9] = {'1','2','3','4','5','6','7','8','9'};


char keys[Filas][Columnas]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinesFilas[Filas]={47,45,43,41};
byte pinesColumnas[Columnas]={39,37,35,33};
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, Filas, Columnas);
     

//////////////////////////////////////////////////


///Fuciones para la pantalla (Interfaz)
void Pantalla_inicio(){
    lcd.setCursor(0, 0);  
    lcd.print("Pasajeros:");
    lcd.setCursor(10, 0);
    lcd.print(pasajeros);
    lcd.setCursor(0, 1);  
    lcd.print("Sig:A");
    lcd.setCursor(10, 1);    
    lcd.print("Guar:D");  
}

void Pantalla_paradero_final(){
    lcd.setCursor(0, 0);  
    lcd.print("P.final:");
    lcd.setCursor(8, 0);
    lcd.print(pfinal);
    lcd.setCursor(0, 1);  
    lcd.print("Sig:A");
    lcd.setCursor(10, 1);    
    lcd.print("Canc:B");

}

void Pantalla_tipo(){
    lcd.setCursor(0, 0);  
    lcd.print("Uni/Esc: A");
    lcd.setCursor(0, 1);  
    lcd.print("General: B");
}
////////////////////////Impresora
void Imprime_vaucher() {
  printer.setSize('M');
  printer.println("*** TU RUTEX ***\n");
  printer.justify('C');
  printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
  printer.println("TOKEN NUMBER");
  printer.justify('C');
  printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
  printer.println("ESC/UNIV");
  printer.boldOn();
  printer.setSize('L');
  printer.println(pfinal);
  printer.boldOff();
  printer.justify('C');
  printer.setSize('S');
  printer.println("***  TEN UN GRAN DÍA  ***");
  printer.justify('C');
  printer.print("DATE:15/10/2019\t");
  printer.println("TIME: 6:14");
  printer.println("TODAY: MARTES");  
  printer.write(10);
  printer.write(10);
  printer.write(10);

}


void setup()
{
    mySerial.begin(9600);  // Initialize SoftwareSerial
    printer.begin();// Init printer (same regardless of serial type)
    lcd.setBacklightPin(3,POSITIVE);  // puerto P3 de PCF8574 como positivo
    lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
    lcd.begin(16, 2);     // 16 columnas por 2 lineas para LCD 1602A
    lcd.clear();      // limpia pantalla
    lcd.setCursor (0,0);
    lcd.print("==> TU RUTEX <==");
    delay(5000);
    lcd.clear();
}

void loop()
{
Tecla = teclado.getKey();  

if (Tecla != 0) {      
    lcd.clear();
    delay(100);
 }

 if(contador == 3){ Pantalla_tipo();accion_4();}
 if(contador == 2){ Pantalla_paradero_final();accion_2();accion_3();}
 if(contador == 1){ Pantalla_inicio();accion_1();}
 
}

  /////////////////////Accion 1 //////////////////////////////
void accion_1(){
  //if(pulsacion == 'D') intermitente();
  if(Tecla == 'A'){lcd.clear();contador=2;}
}

/////////////////////Accion 2 //////////////////////////////
void accion_2(){
  for(int i =0;i < 9; i++){
    if(Tecla == paraderos[i])pfinal= Tecla;
  }
}
  /////////////////////Accion 3 //////////////////////////////
void accion_3(){
  if(Tecla == 'A' && pfinal != ' ') {lcd.clear();contador=3;}
  else{contador == 2;}
  if(Tecla == 'B') {lcd.clear();pfinal = ' ';contador=2;}
  if(Tecla == '*') {lcd.clear();pfinal = ' ';contador=1;}
}

/////////////////////accion 4  //////////////////////////////////
void accion_4(){
  if(Tecla == 'A') {pasajeros++;Imprime_vaucher();lcd.clear();contador=1;pfinal = ' ';}
  if(Tecla == 'B') {pasajeros++;Imprime_vaucher();lcd.clear();contador=1;pfinal = ' ';}
  if(Tecla == '*') {lcd.clear();pfinal = ' ';contador=1;}
}

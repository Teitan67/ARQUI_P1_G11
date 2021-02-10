//Importaciones
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

//Codigo de control de matriz
//Configuracion de las matrices
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 2
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10
int direc_pin =8;
int vel_pin=9;

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

//Parametros Scrolling

uint8_t scrollSpeed = 30;    // velocidad
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;

uint16_t scrollPause = 1000; // en milisegundos

// Global message buffers shared by Serial and Scrolling functions
#define  BUF_SIZE  75
char curMessage[BUF_SIZE] = { "" };
char newMessage[BUF_SIZE] = { "TP1 - GRUPO 11 - SECCION B" };
bool newMessageAvailable = true;


void readSerial(void)
{
  
  static char *cp = newMessage;

  while (Serial.available()){
    *cp = (char)Serial.read();
    if ((*cp == '\n') || (cp - newMessage >= BUF_SIZE-2)){
      *cp = '\0'; // end the string
      
      cp = newMessage;
      newMessageAvailable = true;
    }
    else  // move char pointer to next position
      cp++;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando aplicacion con normalidad...\n");

  P.begin();
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  pinMode(direc_pin,INPUT);
  pinMode(vel_pin,INPUT);
}

void loop() {
  if (digitalRead(direc_pin)==1){
    Serial.println("Cambio de direccion!!");
    if(scrollEffect==PA_SCROLL_RIGHT){
      scrollEffect = PA_SCROLL_LEFT; 
      scrollAlign = PA_LEFT;
    }else{
      scrollEffect = PA_SCROLL_RIGHT;
      scrollAlign = PA_RIGHT;
      
    }
    P.displayClear();// limpia las matrices y se reinicia la animación
    P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    delay(500);
  }
  if (digitalRead(vel_pin)==1){
    Serial.println("Cambio de Velocidad!!");
    if(scrollSpeed==30){
      scrollSpeed=100;
    }else{
      scrollSpeed=30;
    }
    P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    delay(500);
  }
  if (P.displayAnimate())
  {
    if (newMessageAvailable)
    {
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
    }
    P.displayReset();
  }
  readSerial();

}

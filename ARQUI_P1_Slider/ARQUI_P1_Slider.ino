#include <MatrizLed.h>
int data = 4;
int load = 3;
int clk = 2;
int matrix = 2;    //Numero de displays a usar  
MatrizLed pantalla;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando aplicacion con normalidad...\n");
  pantalla.begin(data, clk, load, matrix); // dataPin, clkPin, csPin, numero de matrices de 8x8
  pantalla.rotar(true);
}

void loop() {
  pantalla.borrar();
  pantalla.escribirFraseScroll("TP1 - GRUPO 11 - SECCION B",5); // Texto, posicion en la pantalla

}

/* ----------------------------------------------------------- */
/*            Control de Camara con Protocolo VISCA            */
/*                   Autor: Alfredo Valdés                     */
/* ----------------------------------------------------------- */

/***************** Declaracion de dependencias *****************/

#include <Frame_V8.h>
#include <SerialFunctions_V8.h>
#include <SendOnlySoftwareSerial.h>
#include "Messages.h"

/********************* Definicion de pines **********************/

#define IluminacionPin  6
#define ActiveComm 9
#define led 13

/****************** Declara variables globales ******************/

SendOnlySoftwareSerial Sserial (A5); //Send to camera via RS232
Frame message; //Pass parameters from computer to MCU
char NewData [] = {0, 0, 0, 0, 0, 0}; // Message is stored here
int NoData = 0;
int Function = 0;
int Data = 0;
int flag = 0; // Verify if there is a new message
static int ledState = 1;    // on
char displayFecha[16] = {0x81, 0x01, 0x04, 0x73, 0x20, 0x05, 0x03, 0x03, 0x4E, 0x0C, 0x0C, 0x4E, 0x18, 0x18, 0x1B, 0xFF};
char displayHora[16] = {0x81, 0x01, 0x04, 0x73, 0x30, 0x13, 0x07, 0x07, 0x4A, 0x0C, 0x0C, 0x4A, 0x12, 0x12, 0x1B, 0xFF};

/******************** Inicializa todo ********************/

void setup() {
  initSerial();
  Sserial.begin(9600);
  pinMode(ActiveComm, OUTPUT);     // Enable RS485
  pinMode(led, OUTPUT);            // Led
  pinMode(IluminacionPin, OUTPUT); // Iluminacion
    Enviar(StartUp);
  Enviar(Clear);

  Enviar(cleartitle);
  Enviar(showtitle);
  digitalWrite(led, ledState);    // Start with the led on
  digitalWrite(ActiveComm, HIGH);  // To send to Robot

}

// Loop
void loop() {

  // From PC
  if (Serial.available())
  {
    NoData = readFrame(&message);
    if (NoData && validateFrame(&message))
    { // if data available
      //Function = message.function;
      flag = 1;

      if (message.function == 8) {
        if (message.data[0] == 1) {
          Enviar(CameraOn);
        }
        if (message.data[0] == 0) {
          Enviar(CameraOff);
        }
      }
      if (message.function == 9) {
        if (message.data[0] == 1) {
          Enviar(MenuOn);
        }
        if (message.data[0] == 0) {
          Enviar(MenuOff);
        }
      }
      if (message.function == 12) {
        if (message.data[0] == 1) {
          Enviar(MenuUp);
          Enviar(ZoomStop);
        }
        if (message.data[0] == 2) {
          Enviar(MenuRight);
          Enviar(FocusStop);
        }
        if (message.data[0] == 3) {
          Enviar(MenuDown);
          Enviar(ZoomStop);
        }
        if (message.data[0] == 4) {
          Enviar(MenuLeft);
          Enviar(FocusStop);
        }
      }
      if (message.function == 7) {
        SliderToPosZoom(message.data[0]);
      }
      if (message.function == 11) {
        analogWrite(IluminacionPin, message.data[0]);
      }
      if (message.function == 13) {
        if (message.data[0] == 1) {
          Enviar(cleartitle);
          displayFecha[6] = 0x00;
          displayFecha[7] = 0x00;
          displayFecha[6] = message.data[1] + 29;
          displayFecha[7] = message.data[2] + 29;
        }
        if (message.data[0] == 2) {
          displayFecha[9] = 0x00;
          displayFecha[10] = 0x00;
          displayFecha[9] = message.data[1] + 29;
          displayFecha[10] = message.data[2] + 29;
        }
        if (message.data[0] == 3) {
          displayFecha[12] = 0x00;
          displayFecha[13] = 0x00;
          displayFecha[12] = message.data[1] + 29;
          displayFecha[13] = message.data[2] + 29;
          for (int i = 6; i < 14; i++) {
            if (displayFecha[i] == 29) {
              displayFecha[i] = 39;
            }
          }
          for (int i = 0; i < 16; i++) {
            Sserial.write(displayFecha[i]);
          }
        }
        if (message.data[0] == 4) {
          displayHora[6] = 0x00;
          displayHora[7] = 0x00;
          displayHora[6] = message.data[1] + 29;
          displayHora[7] = message.data[2] + 29;
        }
        if (message.data[0] == 5) {
          displayHora[9] = 0x00;
          displayHora[10] = 0x00;
          displayHora[9] = message.data[1] + 29;
          displayHora[10] = message.data[2] + 29;
        }
        if (message.data[0] == 6) {
          displayHora[12] = 0x00;
          displayHora[13] = 0x00;
          displayHora[12] = message.data[1] + 29;
          displayHora[13] = message.data[2] + 29;
          for (int i = 6; i < 14; i++) {
            if (displayHora[i] == 29) {
              displayHora[i] = 39;
            }
          }
          for (int i = 0; i < 16; i++) {
            Sserial.write(displayHora[i]);
          }
        }
        Enviar(showtitle);
      }
      Send485();
      ledState = !ledState;
      digitalWrite(led, ledState);
    }
  }
  digitalWrite(ActiveComm, LOW);  // To Recive


}
void Enviar(char dato[]) {
  for (int i = 0; i < 6; i++) {
    Sserial.write(dato[i]);
  }
}

char SliderToPosZoom(int data) {
  int val = map(data, 0, 255, 0, 32768);
  char arreglo[4] = {((val >> 12) & 0xF), ((val >> 8) & 0xF), ((val >> 4) & 0xF), (val & 0xF)};
  char ZoomPos[9] = {0x81, 0x01, 0x04, 0x47, arreglo[0], arreglo[1], arreglo[2], arreglo[3], 0xFF};
  for (int i = 0; i < 9; i++) {
    Sserial.write(ZoomPos[i]);
  }
}


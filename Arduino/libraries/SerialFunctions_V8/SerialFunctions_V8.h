#ifndef SerialFunctions_V8_H
#define SerialFunctions_V8_H

#include <Frame_V8.h>
//#include <cstring>


//Estas funciones son especificas para Arduino

int initSerial();

//Envio y Recepcion del serial de Hardware

int sendFrame(Frame *testFrame);
int readFrame(Frame *testFrame);

#endif // SerialFunctions_H

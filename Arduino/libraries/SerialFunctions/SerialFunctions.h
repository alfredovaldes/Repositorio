#ifndef SerialFunctions_H
#define SerialFunctions_H

#include <Frame_V6.h>
//#include <cstring>


//Estas funciones son especificas para Arduino

int initSerial();

//Envio y Recepcion del serial de Hardware

int sendFrame(Frame *testFrame);
int readFrame(Frame *testFrame);

#endif // SerialFunctions_H

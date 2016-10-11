/* Este es el include para la trama version arduino */

#ifndef Frame_V8_H
#define Frame_V8_H

#include "Arduino.h"

#define frameBuffSize 8
#define dataSize 6

typedef struct
{
    char function;
    char data[dataSize];
    char checkSum;
} __attribute__((__packed__))Frame;

int makeFrame(Frame *testFrame, char newFunction, char *newData);

char getCheckSum(Frame *testFrame);

int validateFrame(Frame *testFrame);

#endif // frame_H

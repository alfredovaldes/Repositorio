#include "Arduino.h"
#include <SerialFunctions.h>

char pBuffer[frameBuffSize];

int initSerial()
{
	//Serial.begin(9600);
	Serial.begin(57600);
	return 0;
}

int sendFrame(Frame *testFrame)
{
	//char pBuffer[frameBuffSize];

	memcpy(pBuffer, testFrame, frameBuffSize);

	for(int i = 0; i<frameBuffSize;i++) {
		Serial.write(pBuffer[i]);
	 }

	return 0;
}

int readFrame(Frame *testFrame)
{
	int counter = 0;
	for(int i=0; i<frameBuffSize;i++)	// Clean the Buffer
		pBuffer[i] = 0;

	int byteCounter = 0;
	// Espera a que se junten "frameBuffSize" bytes
	while(byteCounter < frameBuffSize){
		if (Serial.available()) {
			pBuffer[byteCounter] = Serial.read();
			byteCounter++;
		} else {
			delayMicroseconds(1200);
			//delayMicroseconds(138);
			counter++;
			if (counter > frameBuffSize) {
				memcpy(testFrame, pBuffer, frameBuffSize);
				return 1;
			}
		}
	}

	memcpy(testFrame, pBuffer, frameBuffSize);

	return 0;
}


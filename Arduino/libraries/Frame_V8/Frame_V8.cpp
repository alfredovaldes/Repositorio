#include "Frame_V8.h"


int makeFrame(Frame *testFrame, char newFunction, char *newData)
{
	if(testFrame == 0)
		return -1;

	int i;

	testFrame->function = newFunction;
	for(i = 0;i<dataSize;i++)
		testFrame->data[i] = newData[i];
	testFrame->checkSum = getCheckSum(testFrame);

	return 0;
}

char getCheckSum(Frame *testFrame)
{
	int i;
	char checksum = 0;
	char tempFrameBuffer[frameBuffSize];
	memcpy(tempFrameBuffer, testFrame, frameBuffSize);

	for(i = 0; i<frameBuffSize-1; i++)
	{
	   checksum+= tempFrameBuffer[i];
	}

	return(checksum);
}

int validateFrame(Frame *testFrame)
{
    char checksum = getCheckSum(testFrame);

    if(checksum == testFrame->checkSum)
        return 0;
    else
        return 1;

}

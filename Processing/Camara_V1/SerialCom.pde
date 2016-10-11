import processing.serial.*;
Serial myPort;  // The serial port

int frameBuffSize = 6;
int dataSize = 4;

int[] pBuffer = new int[frameBuffSize];
int[] rBuffer = new int[frameBuffSize];

void setupComm(int OptCom)
{
    int Baud = 57600;
  
    // List all the available serial ports
    println("Available ports:");
    println(Serial.list());
    println(" ");
    // Open the port you are using at the rate you want:
    myPort = new Serial(this, Serial.list()[OptCom], Baud);
}



void makeFrame(int newFunction, int newData1, int newData2, int newData3, int newData4)
{
    pBuffer[0] = newFunction;
    pBuffer[1] = newData1;
    pBuffer[2] = newData2;
    pBuffer[3] = newData3;
    pBuffer[4] = newData4;
  
    pBuffer[5] = getCheckSum();
}


int getCheckSum()
{
  int i;
  int checksum = 0;

  for(i = 0; i<frameBuffSize-1; i++)
  {
     checksum+= pBuffer[i];
  }
  
  return checksum;

}


// --------- Send Recive functions -----

int SendFrameSerial()
{
  
  for(int i = 0; i<frameBuffSize;i++) {
    myPort.write(pBuffer[i]);
   }

  return 0;
}

int readFrameHardSerial()
{
    int counter = 0;
    for(int i=0; i<frameBuffSize;i++)  // Clean the Buffer
        rBuffer[i] = 0;
  
    int byteCounter = 0;
    // Espera a que se junten "frameBuffSize" bytes
    while(byteCounter < frameBuffSize){
        if (myPort.available() > 0) {
            rBuffer[byteCounter] = myPort.read();
            byteCounter++;
            counter = 0;
        } else {
            counter++;
            if (counter > frameBuffSize) {
                return 1;
            }
        }
    }
  
    return 0;
}

// -------------- READ FRAME ------------
void ReadPort()
{
    if(myPort.available()>0){
          int NoData = readFrameHardSerial();
          //if(!NoData && !validateFrame(&message)){  // if data available
          if(NoData == 0){
              print(rBuffer[0]); print(' ');
              print(rBuffer[1]); print(' ');
              print(rBuffer[2]); print(' ');
              print(rBuffer[3]); print(' ');
              print(rBuffer[4]); print(' ');
              println(rBuffer[5]);
/*              if(rBuffer[0] == 1){    // Gas Sensor
                  Gas = rBuffer[1];
                  //Volt = rBuffer[2];
              }  
              if(rBuffer[0] == 2){     // Humidity Sensor
                  Temp1 = rBuffer[1];
                  Hum = rBuffer[2];
              }
              if(rBuffer[0] == 3){     // Humidity Sensor
                  Temp2 = rBuffer[1];
                  Press = rBuffer[2];
              }*/
          }
     }
}
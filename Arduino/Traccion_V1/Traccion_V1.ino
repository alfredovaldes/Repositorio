#include <Frame_V8.h>
#include <SerialFunctions_V8.h>    // Include hardware Serial functions
#include <Wire.h>
#include "EasyTransferI2C.h"


// Frame to read/send information
Frame message;
char NewData [] = {0, 0, 0, 0, 0, 0};
int NoData = 0;

int Function = 0;
int Data = 0;
int flag = 0;         // Verify if there is a new message

//create I2C object
EasyTransferI2C ET;

struct RECEIVE_DATA_STRUCTURE {
  float yawAct;
  float pitchAct;
  float rollAct;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

//define slave i2c address
#define I2C_SLAVE_ADDRESS 8

/*
  PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM



  Active485                               <- FALTA

  Control tracction's velocity from 0 to 255
*/
// -------------- Pins definitions -----------------------


#define ActiveComm 9
#define led 13

// Led
static int ledState = 1;    // on



// ------------------ Initializa everything --------------------------
void setup() {
  // initialize serial
  initSerial();

  Wire.begin(I2C_SLAVE_ADDRESS);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Wire);
  //define handler function on receiving data
  Wire.onReceive(receive);

  pinMode(ActiveComm, OUTPUT);     // Enable the rs485
  pinMode(led, OUTPUT);            // Led



  digitalWrite(led, ledState);    // Start with the led on
  digitalWrite(ActiveComm, HIGH);  // To send to Robot
  mydata.yawAct = 0.0;
  mydata.pitchAct = 0.0;
  mydata.rollAct = 0.0;
}


// Loop
void loop() {

  // From PC
  if ((ET.receiveData())&&(Serial.available()))
  {
    NoData = readFrame(&message);
    //if(!NoData)
    if (!NoData && !validateFrame(&message))
    { // if data available
      //Function = message.function;
      flag = 1;

      if (message.function == 4) {
        GetMagDir(0, 1, mydata.yawAct);
        GetMagDir(2, 3, mydata.pitchAct);
        GetMagDir(4, 5, mydata.rollAct);

        message.checkSum = getCheckSum(&message);
      }

      if (message.function == 1) {
        // Motor traccion
      }

      Send485();

      ledState = !ledState;
      digitalWrite(led, ledState);
    }
  }
  digitalWrite(ActiveComm, LOW);  // To Recive


}



void GetMagDir(int Pos1, int Pos2, float Var) {
  if (Var > 0) {
    message.data[Pos1] = Var;
    message.data[Pos2] = 0;
  }
  else {
    message.data[Pos1] = -Var;
    message.data[Pos2] = 1;
  }
}

void receive(int numBytes) {}

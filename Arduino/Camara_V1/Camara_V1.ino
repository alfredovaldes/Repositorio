//#include <MsTimer2.h>          // Pins 3 and 11
#include <Frame_V6.h>
#include <SerialFunctions.h>    // Include hardware Serial functions
#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial Sserial (A5);

// Frame to read/send information
Frame message;
char NewData [] = {0, 0, 0, 0};
int NoData=0;

int Function = 0;
int Data = 0;
int flag = 0;         // Verify if there is a new message

/*
  Arduino NANO
  PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM

  
  
  Active485                               <- FALTA
  
  Control tracction's velocity from 0 to 255
*/  
// -------------- Pins definitions -----------------------


#define IluminacionPin  6
#define ActiveComm 9
#define led 13

// Led
static int ledState = 1;    // on



// ------------------- Time interruption Function ---------------
void TimeInt() 
{
    
}

// ------------------ Initializa everything --------------------------
void setup() { 
    // initialize serial
    initSerial();
        
    pinMode(ActiveComm, OUTPUT);     // Enable the rs485
    pinMode(led, OUTPUT);            // Led
    pinMode(IluminacionPin, OUTPUT); // Iluminacion
    
    //ServoRoll.attach(ServoRollPin);
    //ServoTill.attach(ServoTillPin);
    //ServoLaser_1.attach(ServoLaserPin_1);
    //ServoLaser_2.attach(ServoLaserPin_2);
    
    
    digitalWrite(led, ledState);    // Start with the led on
    digitalWrite(ActiveComm, HIGH);  // To send to Robot
    //MsTimer2::set(20, TimeInt);       // period
    //MsTimer2::start();
} 

// Loop
void loop() {  
    
    // From PC
    if(Serial.available())
    {
        NoData = readFrame(&message);
        if(NoData && validateFrame(&message))
        {   // if data available
            //Function = message.function;
            flag = 1;
            
            if(message.function == 12){
              if(message.data1[0] == 1){
                
              }
              
                // Motor code here
            }
            
            if(message.function == 11){
                analogWrite(IluminacionPin,message.data1[0]);
            }
            
            Send485();
  
            ledState = !ledState;
            digitalWrite(led, ledState);
        }
    }
    digitalWrite(ActiveComm, LOW);  // To Recive
    
    
} 


#include <SoftwareSerial.h>
#define ledPin 13 // Led 
#define Active485_1 6
#define Active485_2 7



byte incomingByte = 0;   // for incoming serial data
int ledState = LOW;  

byte address_set[4]= {0x88, 0x30, 0x01, 0xFF};
byte if_clear[5]= {0x88, 0x01, 0x00, 0x01, 0xFF};
byte zoom_teleVar2[6]= {0x81, 0x01, 0x04, 0x07, 0x31, 0xFF}; //zoom in 81 01 04 07 2p FF - p=0 (low) to 7 (high)
byte zoom_teleVar3[6]= {0x81, 0x01, 0x04, 0xDF, 0x32, 0xFF}; //zoom in 81 01 04 07 2p FF - p=0 (low) to 7 (high)
byte zoom_stop[6]= {0x81, 0x01, 0x04, 0x07, 0x00, 0xFF}; //stop zoom
//const int thisdelay= 250; //time between sets

void setup() {

    Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
    Serial1.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(Active485_1, OUTPUT);
    pinMode(Active485_2, OUTPUT);

    digitalWrite(Active485_1, HIGH); 
    digitalWrite(Active485_2, HIGH); 
    Serial.println("START");
    delay(500);
    
    //send Address set
    for (int i=0; i<4; i++){
        Serial1.write(address_set[i]);
        Serial.write(address_set[i]);
    }
    delay(500);
    //send IF_clear set
    for (int i=0; i<5; i++){
        Serial1.write(if_clear[i]);
        Serial.write(if_clear[i]);
        delay(100);
    }
    Serial.println("TEST");
}

void loop() {

    // send data only when you receive data:
    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();

        if (incomingByte == 49){
            ledState = !ledState;
            digitalWrite(ledPin, ledState);
            //Send zoom tele set
            for (int i=0; i<6; i++){
                Serial1.write(zoom_teleVar2[i]);
                Serial.write(zoom_teleVar2[i]);
            }
        }

        if (incomingByte == 50){
            ledState = !ledState;
            digitalWrite(ledPin, ledState);
            //Send zoom tele set
            for (int i=0; i<6; i++){
                Serial1.write(zoom_teleVar3[i]);
                Serial.write(zoom_teleVar3[i]);
            }
        }

            
        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte);
    }
    
}

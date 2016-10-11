
// --------------- Send to Robot ---------------------
void Send485(){
    //digitalWrite(ActiveComm, HIGH);  // Active the 485
    //delayMicroseconds(600);
    sendFrame(&message);  // 
    //delayMicroseconds(1800);    
}


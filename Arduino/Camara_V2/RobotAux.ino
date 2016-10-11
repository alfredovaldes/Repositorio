
// --------------- Send to Robot ---------------------
void Send485(){
    //digitalWrite(ActiveComm, HIGH);  // Active the 485
    //delayMicroseconds(600);
    sendFrame(&message);  // 
    //delayMicroseconds(1800);    
}

void Send232(int dato[]) {
  for (int i = 0; i < 9; i++) {
    Serial.print((dato[i]),HEX);
  }
  delay(500);
}

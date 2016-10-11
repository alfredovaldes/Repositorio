/**
 * Reading and displaying an image from an attached Capture device. 
 **/

int ScaleTime = 200;  // milisegundos, tiempo para mandar datos

int SizeX = 1024;
int SizeY = 768;

boolean flag =true;

void setup() {
  size(1024, 768);        // 640 X 480
  //size(1300, 1000);        // 1280 X 960

  setupComm(0);      // Puerto a seleccionar
  SetupButtons();    // Inicion de botones
  savedTime = millis();
}

void draw() {
  if (flag) {
    delay(1500);
    int d = day();    // Values from 1 - 31
    int m = month();  // Values from 1 - 12
    int y = year()-2000;   // 2003, 2004, 2005, etc.
    int du=d%10;
    int dd=d/10;
    int mu=m%10;
    int md=m/10;
    int yu=y%10;
    int yd=y/10;
    int s = second();  // Values from 0 - 59
    int min = minute();  // Values from 0 - 59
    int h = hour();
    int su=s%10;
    int sd=s/10;
    int minu=min%10;
    int mind=min/10;
    int hu=h%10;
    int hd=h/10;
    makeFrame(13, 1, dd, du, 0);
    SendFrameSerial();
    delay(100);
    makeFrame(13, 2, md, mu, 0);
    SendFrameSerial();
    delay(100);
    makeFrame(13, 3, yd, yu, 0);
    SendFrameSerial();
    delay(100);
    makeFrame(13, 4, hd, hu, 0);
    SendFrameSerial();
    delay(100);
    makeFrame(13, 5, mind, minu, 0);
    SendFrameSerial();
    delay(100);
    makeFrame(13, 6, sd, su, 0);
    SendFrameSerial();
    delay(100);
    flag = false;
  }
  background(myColor);    // Clean the background
  DrawCircle();
  ReadPort();
  TimerFunc();
}
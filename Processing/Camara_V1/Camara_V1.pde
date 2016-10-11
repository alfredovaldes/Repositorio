/**
 * Reading and displaying an image from an attached Capture device. 
**/

int ScaleTime = 200;  // milisegundos, tiempo para mandar datos

int SizeX = 800;
int SizeY = 600;

void setup() {
    size(800, 600);        // 640 X 480
    //size(1300, 1000);        // 1280 X 960
    
    setupComm(0);      // Puerto a seleccionar
    SetupButtons();    // Inicion de botones
    
    savedTime = millis();
}

void draw() {
    background(myColor);    // Clean the background
    DrawCircle();
    ReadPort();
    
    TimerFunc();
    
}
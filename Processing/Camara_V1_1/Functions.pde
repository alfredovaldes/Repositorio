int VelCam_T = 0;    // For the camera velocity
int DirCam_T = 0;    // For the camera velocity
int VelCam_P = 0;    // For the camera velocity
int DirCam_P = 0;    // For the camera velocity

int VelTrac_I = 0;    // For the traction velocity
int DirTrac_I = 0;    // For the traction velocity
int VelTrac_D = 0;    // For the traction velocity
int DirTrac_D = 0;    // For the traction velocity
int Ilum = 0;     // For ilumination
int ZoomPos = 0;
boolean state=false;
int[] VelDir = {0, 0};

//int flagTime = 0;
//int flagOption = 0;
int savedTime;
int Count = 0;
int Val = 0;          // Inicio del numero de imagen

boolean flagTraccion = false;
boolean flagCamera = false;
boolean flagIlum = false;
boolean flagZoom = false;


// -------------- Buttons ------------

public void StopTraccionMotor() {
    makeFrame(1, 0, 0, 0, 0);
    SendFrameSerial();
}

public void StopCameraMotor() {
    makeFrame(10, 0, 0, 0, 0);
    SendFrameSerial();
}

public void Arriba() {
    makeFrame(12, 1, 0, 0, 0);
    SendFrameSerial();
}

public void Derecha() {
    makeFrame(12, 2, 0, 0, 0);
    SendFrameSerial();
}

public void Abajo() {
    makeFrame(12, 3, 0, 0, 0);
    SendFrameSerial();
}

public void Izquierda() {
    makeFrame(12, 4, 0, 0, 0);
    SendFrameSerial();
}

public void Send_Traccion() {
    makeFrame(1, DirTrac_I, VelTrac_I, DirTrac_D, VelTrac_D);
    SendFrameSerial(); 
    
}

public void Send_Camera() {
    makeFrame(10, DirCam_T, VelCam_T, DirCam_P, VelCam_P);
    SendFrameSerial(); 
}


public void Send_Ilum() {
    makeFrame(11, Ilum, 0, 0, 0);
    SendFrameSerial(); 
}
public void Send_Zoom() {
    makeFrame(7, ZoomPos, 0, 0, 0);
    SendFrameSerial(); 
}


public void TimerFunc(){
    int passedTime = millis() - savedTime;
    if ((passedTime > ScaleTime)) 
    {
        if (flagCamera == true) 
        {
            flagCamera = false;
            VelDir = VelocidadDireccion(VelCam_T);
            VelCam_T = VelDir[0];
            DirCam_T = VelDir[1];
            
            VelDir = VelocidadDireccion(VelCam_P);
            VelCam_P = VelDir[0];
            DirCam_P = VelDir[1];
            
            Send_Camera();
        }
        
        if (flagTraccion == true) 
        {
            flagTraccion = false;
            VelDir = VelocidadDireccion(VelTrac_I);
            VelTrac_I = VelDir[0];
            DirTrac_I = VelDir[1];
            
            VelDir = VelocidadDireccion(VelTrac_D);
            VelTrac_D = VelDir[0];
            DirTrac_D = VelDir[1];
            
            
            Send_Traccion();
        }
        else if(flagIlum == true)
        {
            flagIlum = false;
            Send_Ilum();
        }
         else if(flagZoom == true)
        {
            flagZoom = false;
            Send_Zoom();
          }
       
        
        savedTime = millis();

    }
}


int[] VelocidadDireccion(int Vel) { 
    int Dir;
    if(Vel > 0)
    {
        Dir = 0;
    }
    else 
    {
      Dir = 1;
      Vel = - Vel;
    }
    int[] RetVelDir = {Vel, Dir};
        
  return RetVelDir;  // Returns an array of 3 ints: 20, 40, 60 
}
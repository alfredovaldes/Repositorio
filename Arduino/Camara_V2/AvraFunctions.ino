// Control
float P, I;
float Pp = 2;                 // Proportional Gain
float Pi = 0.1;              // Integral Gain
//float Pd = 0.0;           // Derivative Gain
int Error_Anterior = 0;
int Error = 0;
//int Salida = 0;
//int Salida_aux = 0;
//int flag_int = 1;         // 0 control - 1 Open loop


// -------------- Function to control ---------------------
int Control(int Referencia, int ValSensor) {
    int Salida = 0;
    Error = Referencia - ValSensor;
    
    P = Error * Pp;
    //D = (Error - Error_Anterior) * Pd;
    I = I + (Error * Pi);
    Error_Anterior = Error;
    
    // -------------- Limit the control --------------------
    I = MaxLimit(I,250);
    I = MinLimit(I,-250);
    P = MaxLimit(P,50);
    P = MinLimit(P,-50);
    
    //Salida = P + I + D;
    Salida = P + I;
    return Salida;
}

// ----------------- Function to control --------------------
int OpenLoop(int Entrada) {
    int Salida = 0;
    Salida  = Entrada;
    return Salida;
}

// -------------------------- Max Output limit --------------
int MaxLimit(int Output, int MaxLim){
  if(Output > MaxLim) {  // If it´s bigger, put max velocity (real 255)
    Output = MaxLim;
  } 
  return Output;
}

//  ---------------------- Min Output limit --------------
int MinLimit(int Output, int MinLim){
    if(Output < MinLim) {  // If it´s smaller, put max velocity (real 255)
        Output = MinLim;
    } 
    return Output;
}

// ----------------- Smooth function ---------------------
int Smooth(int Desired, int Desired_Smooth){
    int Step = 5;    // The steps to increase/decrease
    if (Desired == 0) {
        return 0;    // If zero,return zero
    }
    if (Desired > Desired_Smooth) {
        if ( (Desired + Step) > Desired_Smooth) {
            Desired_Smooth = Desired_Smooth + Step;
        }
        else { Desired_Smooth++;}
    }
    else if (Desired == Desired_Smooth) {
        Desired_Smooth = Desired;
    }
    else {
        if ( (Desired - Step) < Desired_Smooth) {
            Desired_Smooth = Desired_Smooth - Step;
        }
        else { Desired_Smooth--;}
    }
    return Desired_Smooth;
}


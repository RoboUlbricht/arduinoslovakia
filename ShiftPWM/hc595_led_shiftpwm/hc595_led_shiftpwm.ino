#define SHIFTPWM_USE_TIMER2

const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 1;
int numRGBleds = numRegisters*8/3;

unsigned char val[8]={
  255,200,150,100,80,60,40,0};

void setup() {
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  ShiftPWM.PrintInterruptLoad();

  for(int i=0;i<8;i++)
  {
    unsigned char v=val[i];  
    ShiftPWM.SetOne(i,v);  
  }  
}

void loop() {
}








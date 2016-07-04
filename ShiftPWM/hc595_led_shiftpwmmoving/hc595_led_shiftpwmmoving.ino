#define SHIFTPWM_USE_TIMER2

const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 1;
int numRGBleds = numRegisters*8/3;

void setup() {
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  ShiftPWM.PrintInterruptLoad();
}

unsigned char val[8]={
  255,200,120,100,80,20,5,0};
int x=0;

void loop() {
  for(int i=0;i<8;i++)
  {
    int idx=x+i;
    if(idx>7) idx-=8;
    unsigned char v=val[idx];  
    ShiftPWM.SetOne(i,v);  
  }
  x++;  
  if(x>7) x=0;
  delay(100);
}







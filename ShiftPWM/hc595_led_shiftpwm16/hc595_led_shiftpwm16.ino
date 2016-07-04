/*
 * Copyright (c) 2014 Robert Ulbricht
 *
 * Projekt: Arduino
 * Obsah: 
 * Nastavenie 16 LED tak, ze na okraji svietia silno a postupne
 * ku stredu zhasinaju.
 * Created: 02.06.2014 
 */

#define SHIFTPWM_USE_TIMER2

const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 2;
int numRGBleds = numRegisters*8/3;

unsigned char val[16]={
  255,200,150,100,80,60,40,10,
  10,40,60,80,100,150,200,255};

void setup() {
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  ShiftPWM.PrintInterruptLoad();

  ShiftPWM.SetOne(11,255); 
  for(int i=0;i<16;i++)
  {
    unsigned char v=val[i];  
    ShiftPWM.SetOne(i,v);  
  }  
}

void loop() {
}









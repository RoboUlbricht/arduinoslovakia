/*
 * Copyright (c) 2014 Robert Ulbricht
 *
 * Projekt: Arduino
 * Obsah: 
 * Padajuca hviezda. 16 LED sa postupne rozsvieti tak, aby sa
 * zdalo, ze sa pohybuje svietiaci bod, ktory postupne hasne.
 * Created: 02.06.2014 
 */

#define SHIFTPWM_USE_TIMER2
#define LED_COUNT 16

const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 2;

void setup() {
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  ShiftPWM.PrintInterruptLoad();
}

unsigned char val[LED_COUNT]={
  0,0,0,0,0,0,0,0,
  255,200,120,100,80,20,5,0};
int x=0;

void loop() {
  for(int i=0;i<LED_COUNT;i++)
  {
    int idx=x+i;
    if(idx>LED_COUNT-1) idx-=LED_COUNT;
    unsigned char v=val[idx];  
    ShiftPWM.SetOne(i,v);  
  }
  x++;  
  if(x>LED_COUNT-1) x=0;
  delay(100);
}








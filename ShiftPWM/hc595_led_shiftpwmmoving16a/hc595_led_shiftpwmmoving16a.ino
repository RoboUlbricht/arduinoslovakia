/*
 * Copyright (c) 2014 Robert Ulbricht
 *
 * Projekt: Arduino
 * Obsah: 
 * Animacia farebneho bodu, ktory sa pohybuje v poli 16 LED
 * a zanechava po sebe svietiacu stopu, ktora postupne hasne.
 * Created: 02.06.2014 
 */

//#define SHIFTPWM_USE_TIMER2
#define LED_COUNT 16
#define FADE_SPEED 40

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
  0,0,0,0,0,0,0,0};

struct Point
{
int pos;
int dir;
};

Point points[2]={
  {0,1},{LED_COUNT-1,-1}
};

void loop() {
  // nastavenie LED
  for(int i=0;i<LED_COUNT;i++)
  {
    unsigned char v=val[i];  
    ShiftPWM.SetOne(i,v);  
  }
  
  // efekt zhasinania
  for(int i=0;i<LED_COUNT;i++)
    if(val[i]>FADE_SPEED)
      val[i]-=FADE_SPEED;
    else
      val[i]=0;  
      
  // pohybujuci sa bod
  for(int k=0;k<2;k++)
    {
    val[points[k].pos]=255;
    points[k].pos+=points[k].dir;
    if(points[k].pos==LED_COUNT)
      {
      points[k].pos=LED_COUNT-1;
      points[k].dir=-1;  
      }
    if(points[k].pos<0)
      {
      points[k].pos=0;
      points[k].dir=1;  
      }
    }
    
  delay(100);
}







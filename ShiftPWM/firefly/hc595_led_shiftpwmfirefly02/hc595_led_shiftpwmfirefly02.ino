/**
 * Arduino Uno - Firefly simulator 16 LED
 * v. 2.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/ .
 */

//#define SHIFTPWM_USE_TIMER2
#define DELAY_MS 20

const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!
#include "light.h"
#include "pattern.h"
#include "firefly.h"

const unsigned char maxBrightness = 255;
const unsigned char pwmFrequency = 75;
const int numRegisters = 2;
const int ffCount = numRegisters*8;

int r=0;
long mil;
unsigned char value;

firefly f[ffCount];

//#define DEBUG_PRINT
#include "debug.h"

void setup() {
  // debug output
  initDebug();

  // ShiftPWM
  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  #ifdef DEBUG_PRINT
  ShiftPWM.PrintInterruptLoad();
  #endif

  // random init from unconnected analog input
  randomSeed(analogRead(0));
}

void loop() {
  mil=millis();
  for(int i=0;i<ffCount;i++)
  {
    switch(f[i].state)
    {
    case ffIdle:
      r=random(2000);
      if(r<10)
        {
        f[i].state=ffActive;
        r=random(MAX_PT);
        printActive(i,r,mil);
        f[i].pattern=pt[r].pattern;
        f[i].pos=0;
        f[i].length=pt[r].length;
        f[i].repeat=1+random(3);
        }
      break; 
    case ffActive:
      value=pgm_read_byte(f[i].pattern + f[i].pos);
      value=pgm_read_byte(&table[value]);
      ShiftPWM.SetOne(i,value);
      f[i].pos++;
      if(f[i].pos==f[i].length)
        {
        f[i].repeat--;
        if(f[i].repeat)
          f[i].pos=0;
        }
      if(f[i].pos==f[i].length)
        {
        ShiftPWM.SetOne(i,0);
        f[i].state=ffTired;
        f[i].tired=mil+500+random(10000);
        printTired(i);
        }
      break;  
    case ffTired:
      if(f[i].tired<mil)
        {
        f[i].state=ffIdle;
        printIdle(i,mil);
        }
      break;  
    } 
  } 
  delay(DELAY_MS);
}

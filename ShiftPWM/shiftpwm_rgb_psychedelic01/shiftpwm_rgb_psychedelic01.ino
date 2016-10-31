/**
 * Arduino Uno ShiftPWM RGB LED Psychedelic Colors
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * 8 RGB LEDs. Random color transitions.
 * ShiftPWM: https://github.com/elcojacobs/ShiftPWM
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 3;
int numRGBleds = numRegisters*8/3;

// table of exponential values
// generated for values of i from 0 to 255 -> x=round( pow( 2.0, i/32.0) - 1);
const byte table[] PROGMEM = {
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,
  2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,
  3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,   5,
  5,   5,   5,   5,   5,   5,   5,   6,   6,   6,   6,   6,   6,   6,   7,   7,
  7,   7,   7,   8,   8,   8,   8,   8,   9,   9,   9,   9,   9,  10,  10,  10,
 10,  11,  11,  11,  11,  12,  12,  12,  12,  13,  13,  13,  14,  14,  14,  15,
 15,  15,  16,  16,  16,  17,  17,  18,  18,  18,  19,  19,  20,  20,  21,  21,
 22,  22,  23,  23,  24,  24,  25,  25,  26,  26,  27,  28,  28,  29,  30,  30,
 31,  32,  32,  33,  34,  35,  35,  36,  37,  38,  39,  40,  40,  41,  42,  43,
 44,  45,  46,  47,  48,  49,  51,  52,  53,  54,  55,  56,  58,  59,  60,  62,
 63,  64,  66,  67,  69,  70,  72,  73,  75,  77,  78,  80,  82,  84,  86,  88,
 90,  91,  94,  96,  98, 100, 102, 104, 107, 109, 111, 114, 116, 119, 122, 124,
127, 130, 133, 136, 139, 142, 145, 148, 151, 155, 158, 161, 165, 169, 172, 176,
180, 184, 188, 192, 196, 201, 205, 210, 214, 219, 224, 229, 234, 239, 244, 250
};

void SetRGB(int led, unsigned char r,unsigned char g,unsigned char b) {
  r=pgm_read_byte(&table[r]);
  g=pgm_read_byte(&table[g]);
  b=pgm_read_byte(&table[b]);

  ShiftPWM.SetRGB(led,b,g,r);
}

void setup(){
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  ShiftPWM.SetAll(0);
}

struct rgb {
  int r;
  int g;
  int b;
};

rgb v[2];
rgb val[2];
rgb oldval[2];
int side=0;

void loop()
{  
  if(side==0) {
    val[0].r=random(255);
    val[0].g=random(255);
    val[0].b=random(255);
  } else {
    val[1].r=random(255);
    val[1].g=random(255);
    val[1].b=random(255);
  }

  for(int j=0;j<100;j++) {
    v[0].r=map(j,0,99,oldval[0].r,val[0].r);
    v[0].g=map(j,0,99,oldval[0].g,val[0].g);
    v[0].b=map(j,0,99,oldval[0].b,val[0].b);

    v[1].r=map(j,0,99,oldval[1].r,val[1].r);
    v[1].g=map(j,0,99,oldval[1].g,val[1].g);
    v[1].b=map(j,0,99,oldval[1].b,val[1].b);
    
    for(int i=0;i<8;i++)
      SetRGB(i,
             map(i,0,7,v[0].r,v[1].r),
             map(i,0,7,v[0].g,v[1].g),
             map(i,0,7,v[0].b,v[1].b));
    delay(20);
  }

  oldval[0]=val[0];
  oldval[1]=val[1];

  if(side==0) side=1;
  else side=0;
}

/**
 * Arduino Uno RGB LED Runner
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * 8 RGB LEDs. Basic animation.
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

#include <SPI.h>

//Pin connected to ST_CP of 74HC595
// SS
int latchPin = 10;

//Pin connected to SH_CP of 74HC595
// SCK
int clockPin = 13;

// Pin connected to DS of 74HC595
// MOSI
int dataPin = 11;

const uint8_t numreg595=3;
uint8_t buf[numreg595];
#define RED_BIT 2
#define GREEN_BIT 1
#define BLUE_BIT 0

void bufClear() {
  for(uint8_t i=0;i<3;i++)
    buf[i]=0;
}

void bufSet(uint8_t pos, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t posbitr=pos*3+RED_BIT;
  uint8_t posbitg=pos*3+GREEN_BIT;
  uint8_t posbitb=pos*3+BLUE_BIT;
  r ? bitSet(buf[posbitr/8],posbitr%8) : bitClear(buf[posbitr/8],posbitr%8);
  g ? bitSet(buf[posbitg/8],posbitg%8) : bitClear(buf[posbitg/8],posbitg%8);
  b ? bitSet(buf[posbitb/8],posbitb%8) : bitClear(buf[posbitb/8],posbitb%8);
}

void bufSend() {
  SPI.begin();
  digitalWrite(latchPin, LOW);
  for(uint8_t i=0;i<3;i++)
    SPI.transfer(buf[2-i]);
  digitalWrite(latchPin, HIGH);
}

struct rgb {
  int r;
  int g;
  int b;
};

rgb rgb[7]={
  {1,0,0},
  {0,1,0},
  {0,0,1},
  {1,1,0},
  {0,1,1},
  {1,0,1},
  {1,1,1},
};

void setup() {
  bufClear();
  for(uint8_t i=0;i<7;i++)
    bufSet(i,rgb[i].r,rgb[i].g,rgb[i].b);  
  bufSend();
  delay(5000);
}

void loop() {
  for(uint8_t i=0;i<7;i++)
    for(uint8_t j=0;j<8;j++) {
      bufClear();
      bufSet(j,rgb[i].r,rgb[i].g,rgb[i].b);  
      bufSend();
      delay(50);
    }  
}

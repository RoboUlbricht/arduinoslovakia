/**
 * OHLC Draw
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Few OHLC bars. 2 different algorithms.
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

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

struct OHLCData {
  int o;
  int h;
  int l;
  int c;  
};

OHLCData ohlc[]={
  {1,3,0,2},
  {1,3,0,1},
  {20,40,10,30},
  {30,35,15,20},
  {20,27,16,25},
  {25,43,23,35},
  {35,37,30,31},
};

const int ohlccount=sizeof(ohlc)/sizeof(OHLCData);

void setup() {
  display.begin();
  display.setContrast(60);
  display.clearDisplay();

  for(int j=0;j<=84;j+=2)
    display.drawLine(j,0,j,(j%10==0 ? 2 : 1),BLACK);
  for(int j=0;j<=38;j+=2)
    display.drawLine(0,47-j,(j%10==0 ? 2 : 1),47-j,BLACK);

  for(int i=0;i<ohlccount;i++) {
    drawBarLine(i, &ohlc[i]);
    drawBarBar(i, &ohlc[i]);
  }

  display.display();
}

void loop() {
}

void drawBarLine(int pos, OHLCData *bar) {
  int START = 5 + pos * 6;
  const int BW = 2;
  const int HEIGHT = 47;

  // open
  display.drawLine(START,HEIGHT-bar->o,START+1*BW,HEIGHT-bar->o,BLACK);

  // high - low
  display.drawLine(START+1*BW,HEIGHT-bar->h,START+1*BW,HEIGHT-bar->l,BLACK);

  // close
  display.drawLine(START+1*BW,HEIGHT-bar->c,START+2*BW,HEIGHT-bar->c,BLACK);
}

void drawBarBar(int pos, OHLCData *bar) {
  int START = 40 + pos * 6;
  const int BW = 2;
  const int HEIGHT = 47;
  int top;
  int bottom;

  if(bar->o < bar->c) {
    top = bar->c;
    bottom = bar->o;
  } else {
    top = bar->o;
    bottom = bar->c;
  }

  // high
  display.drawLine(START+1*BW,HEIGHT-bar->h,START+1*BW,HEIGHT-top,BLACK);

  // low
  display.drawLine(START+1*BW,HEIGHT-bar->l,START+1*BW,HEIGHT-bottom,BLACK);

  // bar
  if(bar->o < bar->c) 
    display.drawRect(START,HEIGHT-bottom,2*BW+1,bottom-top+1,BLACK);
  else
    display.fillRect(START,HEIGHT-bottom,2*BW+1,bottom-top+1,BLACK);
}

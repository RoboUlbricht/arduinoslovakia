/**
 * OHLC OLED 0.96 Random Draw With Grid And Autoscale
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Few OHLC bars. 2 different algorithms. Random data are generated as double.
 * 
 * U8g2
 * https://github.com/olikraus/u8g2
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

// If you have more than 2k RAM
//#define BIG_MEMORY

#if defined(BIG_MEMORY)
  #define SSD1306 U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI
#else
  #define SSD1306 U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI
#endif

#include <U8g2lib.h>
#include "candlestick.h"
#include "oled.h"

SSD1306 u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

OHLCChart<double, 19, 10000, OHLCOledBarRender<double> > ohlc;
//OHLCChart<double, 19, 10000, OHLCOledLineRender<double> > ohlc;

double value=22.4;

void setup() {
  Serial.begin(9600);

  u8g2.begin();

  // connect renderer to OLED
  ohlc.getRender().setDisplay(&u8g2);
  ohlc.setGridStep(1.);
}

void loop() {
  // update random data
  int valuemove=random(30)-15;
  value+=valuemove/100.;
  value=constrain(value,10,40);
  //Serial.println(value);
  ohlc.addValue(value);

#if defined(BIG_MEMORY)
  u8g2.clearBuffer();
#else  
  u8g2.firstPage();
  do {
#endif
  u8g2.setFont(u8g2_font_6x10_tn);

  // draw candlesticks
  ohlc.draw();

  // draw last value
  u8g2.setDrawColor(0);
  u8g2.drawBox(5,4,5+5*5+3,11);
  u8g2.setDrawColor(1);
  u8g2.drawFrame(5,4,5+5*5+3,11);
  u8g2.setCursor(7,13);
  u8g2.print(value);

  // draw indicator
  int _v=fmap(value,ohlc.minimum,ohlc.maximum,0.,64.);
  u8g2.drawLine(126,63-_v,128,63-_v);
  u8g2.drawLine(127,63-_v+1,127,63-_v-1);

#if defined(BIG_MEMORY)
  u8g2.sendBuffer(); // transfer internal memory to the display
#else
  } while ( u8g2.nextPage() );
#endif

  delay(200); // 5 values/second
} 


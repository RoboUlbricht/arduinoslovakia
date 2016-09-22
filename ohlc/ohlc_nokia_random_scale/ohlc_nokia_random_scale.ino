/**
 * OHLC Nokia 5110 Random Draw With Grid And Autoscale
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
#include "candlestick.h"

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

// 12 bars, 10 sec/bar, line renderer
//OHLCChart<int, 12, 10000, OHLCNokia5110LineRender<int> > ohlc;

// 12 bars, 10 sec/bar, bar renderer
OHLCChart<int, 12, 10000, OHLCNokia5110BarRender<int> > ohlc;

// 12 bars, 10 sec/bar, serial port renderer
//OHLCChart<int, 12, 10000, OHLCSerialRender<int> > ohlc;

int value=50;

void setup() {
  Serial.begin(9600);

  // connect renderer to Nokia 5110
  ohlc.getRender().setDisplay(&display);
  ohlc.setGridStep(10);

  // Nokia 5110 init
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  display.display();
}

void loop() {
  // update random data
  int valuemove=random(7)-3;
  value+=valuemove;
  value=constrain(value,0,100);
  //Serial.println(value);
  ohlc.addValue(value);

  // render chart
  display.clearDisplay();
  // draw candlesticks
  ohlc.draw();
  // draw last value
  display.fillRect(5,5,15,11,BLACK);
  display.fillRect(6,6,13,9,WHITE);
  display.setCursor(7,7);
  display.print(value);
  // draw indicator
  int _v=map(value,ohlc.minimum,ohlc.maximum,0,47);
  display.drawLine(82,47-_v,83,47-_v,BLACK);
  display.drawLine(83,47-_v+1,83,47-_v-1,BLACK);
  display.display();
  
  delay(200); // 5 values/second
}


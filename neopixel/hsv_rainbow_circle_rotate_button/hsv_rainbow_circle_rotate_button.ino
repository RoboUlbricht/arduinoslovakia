/**
  Arduino Uno - NeoPixel HSV Rainbow Circle Rotation With Gamma Correction
  v. 1.0
  Copyright (C) 2019 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.6 or higher
  Board: Arduino or Arduino Pro Mini

  Libraries
  NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel
  Function setPixelColorHsv is extracted from pull request
  https://github.com/adafruit/Adafruit_NeoPixel/pull/114
  
  U8g2: https://github.com/olikraus/u8g2 
  Version: 2.9.1 or higher 

  OLED | Arduino Pro Mini
  -----|-----------------
  GND  | GND
  VCC  | VCC
  CLK  | 13
  MOSI | 11
  RES  | 8
  DC   | 9
  CS   | 10

  HSV
  https://en.wikipedia.org/wiki/HSL_and_HSV

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Adafruit_NeoPixel.h>
#include <U8g2lib.h>
#include "hsv.h"

// data pin
#define PIN 6
// led count
#define CNT 24
// max Hue
#define MAXHUE 256*6

int position = 0;
int hue = 0;
int oldhue = -1;
char output[128];

U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(CNT, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
}

void loop() {
  // hue - red
  // saturation - max
  // value - 0-255
  for (int i = 0; i < CNT; i++) {
    strip.setPixelColor((i + position) % CNT, getPixelColorHsv(i, hue, 255, strip.gamma8(i * (255 / CNT))));
  }
  strip.show();

  position++;
  position %= CNT;

  if (digitalRead(2) == LOW) {
    hue += 1;
    hue %= MAXHUE;
  }
  if (digitalRead(3) == LOW) {
    hue -= 1;
    if (hue < 0)
      hue = MAXHUE - 1;
  }

  if (oldhue != hue) {
    oldhue = hue;
    sprintf(output, "hue: %d", hue);

    u8g2.firstPage();
    do {
      u8g2.drawStr(16, 32, output); // write something to the internal memory
      for (int j = 0; j <= 128; j += 2)
        u8g2.drawLine(j, 0, j, (j % 10 == 0 ? 2 : 1));
      for (int j = 0; j <= 64; j += 2)
        u8g2.drawLine(0, j, (j % 10 == 0 ? 2 : 1), j);
    } while ( u8g2.nextPage() );
  }

  delay(50);
}

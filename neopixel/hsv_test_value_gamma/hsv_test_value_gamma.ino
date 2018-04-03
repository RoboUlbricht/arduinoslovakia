/**
  Arduino Uno - NeoPixel HSV Value Circle With Gamma Correction
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.5 or higher
  Board: Arduino or Arduino Pro Mini

  Libraries
  NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel
  Function setPixelColorHsv is extracted from pull request
  https://github.com/adafruit/Adafruit_NeoPixel/pull/114

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
#include "hsv.h"

// data pin
#define PIN 6
// led count
#define CNT 24
// max Hue
#define MAXHUE 256*6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(CNT, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  // hue - red
  // saturation - max
  // value - 0-255
  for (int i = 0; i < CNT; i++)
    strip.setPixelColor(i, getPixelColorHsv(i, 0, 255, strip.gamma8(i*(255/CNT))));
  strip.show();
}

void loop() {
}

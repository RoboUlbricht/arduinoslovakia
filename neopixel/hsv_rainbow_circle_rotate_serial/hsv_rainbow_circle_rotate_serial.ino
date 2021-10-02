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

int position = 0;
int hue = 0;
char output[128];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(CNT, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  strip.begin();
}

void loop() {
  // hue - red
  // saturation - max
  // value - 0-255
  for (int i = 0; i < CNT; i++) {
    strip.setPixelColor((i + position) % CNT, getPixelColorHsv(i, hue, 255, strip.gamma8(i * (255 / CNT))));
  }
  strip.show();
  sprintf(output, "hue: %d", hue);
  Serial.println(output);
  position++;
  position %= CNT;
  hue += 2;
  hue %= MAXHUE;
  delay(50);
}

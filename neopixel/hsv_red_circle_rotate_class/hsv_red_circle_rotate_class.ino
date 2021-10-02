/**
  Arduino Uno - NeoPixel HSV Red Circle Rotation With Gamma Correction
  v. 1.0
  Copyright (C) 2021 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.15 or higher
  Board: Arduino or Arduino Pro Mini

  Libraries
  NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel
  v. 1.8.5

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

// data pin
#define PIN 6
// led count
#define CNT 24
// max Hue
#define MAXHUE 65535

Adafruit_NeoPixel ring(CNT, PIN, NEO_GRB + NEO_KHZ800);

class Rotator
{
    Adafruit_NeoPixel *strip;
    int position;
    uint16_t hue;
    uint8_t saturation;

  public:
    Rotator(Adafruit_NeoPixel *npx, int pos = 0, uint16_t h = 0, uint8_t sat = 255);
    void Step();
};

Rotator::Rotator(Adafruit_NeoPixel *npx, int pos, uint16_t h, uint8_t sat)
  : strip(npx), position(pos), hue(h), saturation(sat)
{
}

void Rotator::Step()
{
  // hue - 0-65535
  // saturation - 0-255
  // value - 0-255
  for (int i = 0; i < CNT; i++)
    strip->setPixelColor(
      (i + position) % CNT,
      strip->ColorHSV(hue, saturation, strip->gamma8(i * (255 / CNT))));
  strip->show();
  position++;
  position %= CNT;
}

//Rotator rt(&ring, 0, 0, 255); // red
//Rotator rt(&ring, 0, 0, 200); // pink
Rotator rt(&ring, 0, 40000L, 200); // lightblue

void setup() {
  ring.begin();
}

void loop() {
  rt.Step();
  delay(50);
}

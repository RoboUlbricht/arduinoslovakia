/**
   Arduino Gamma Correction Calculator
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Based on
   https://learn.adafruit.com/led-tricks-gamma-correction?view=all

   Port from Processing to C++.

   IDE: 1.8.3 or higher
   Board: Arduino Pro Mini

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

float    gamma   = 2.8; // Correction factor
uint16_t max_in  = 255; // Top end of INPUT range
uint16_t max_out = 65535; // Top end of OUTPUT range

char output[10];

void setup() {
  Serial.begin(9600);
  Serial.print("const uint16_t PROGMEM gamma[] = {");
  for (int i = 0; i <= max_in; i++) {
    if (i > 0) Serial.print(',');
    if ((i % 16) == 0) Serial.print("\n  ");
    sprintf(output, "%5u", (uint16_t)(pow((float)i / (float)max_in, gamma) * max_out + 0.5));
    Serial.print(output);
  }
  Serial.println("");
  Serial.println("  };");
}

void loop() {
}

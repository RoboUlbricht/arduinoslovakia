/**
   Arduino Traffic Light - Test
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Test of circuit.
    Pin 2 - Red LED - resistor 1k - GND
    Pin 3 - Yellow LED - resistor 1k - GND
    Pin 4 - Green LED - resistor 1k - GND
    Pin 5 - Red LED - resistor 1k - GND
    Pin 6 - Yellow LED - resistor 1k - GND
    Pin 7 - Green LED - resistor 1k - GND

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

int leds[] = {2, 3, 4, 5, 6, 7};
int step = 0;

void setup() {
  for (int i = 0; i < 6; i++)
    pinMode(leds[i], OUTPUT);
}

void loop() {
  for (int i = 0; i < 6; i++)
    digitalWrite(leds[i], i == step ? HIGH : LOW);
  step++;
  step %= 6;
  delay(1000);
}


/**
   ATtiny85 Blink with 5 LED
   v. 1.1
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Turns on one of 5 LEDs for 1/5 second, repeatedly.
   This is tester of my ATtiny85 development board.
   https://www.arduinoslovakia.eu/page/smd-attiny85-vyvojova-doska?lang=en  

   IDE: 1.8.12
   Core: https://github.com/SpenceKonde/ATTinyCore

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

// ATMEL ATTINY85
//
//                  +-\/-+
//      (D 5) PB5  1|    |8  Vcc
//  led (D 3) PB3  2|    |7  PB2 (D 2) led
//  led (D 4) PB4  3|    |6  PB1 (D 1) led
//            GND  4|    |5  PB0 (D 0) led
//                  +----+

const int leds[] = {0, 1, 2, 3, 4};
const int ledcount = sizeof(leds) / sizeof(int);
int step = 0;
const int sleep = 200;

// the setup routine runs once when you press reset:
void setup() {
  for (int i = 0; i < ledcount; i++)
    pinMode(leds[i], OUTPUT);
}

void loop() {
  for (int i = 0; i < ledcount; i++)
    digitalWrite(leds[i], i == step ? HIGH : LOW);
  step++;
  step %= ledcount;
  delay(sleep);
}

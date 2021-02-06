/**
   ATtiny85 Blink
   v. 1.0
   Copyright (C) 2021 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Turns on an LED on for one second, then off for one second, repeatedly.

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
//      (D 3) PB3  2|    |7  PB2 (D 2)
//      (D 4) PB4  3|    |6  PB1 (D 1)
//            GND  4|    |5  PB0 (D 0) led
//                  +----+

#include <util/delay.h>

const int led = 0;
const int sleep = 1000;

int main() {
  // initialize the digital pin as an output.
  bitSet(DDRB, led);
  for (;;) {
    bitSet(PINB, led);
    _delay_ms(sleep);
  }
}

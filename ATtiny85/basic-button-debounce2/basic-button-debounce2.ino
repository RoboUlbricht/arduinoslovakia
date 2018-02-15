/**
   ATtiny85 Button Switch With Debounce
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Switch an LED when button is pushed.

   IDE: 1.8.5
   Core: https://github.com/SpenceKonde/ATTinyCore

   Libraries
   Bounce2: https://github.com/thomasfredericks/Bounce2

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
//      (D 4) PB4  3|    |6  PB1 (D 1) button
//            GND  4|    |5  PB0 (D 0) led
//                  +----+

#include <Bounce2.h>

const int led = 0;
const int button = 1;
int led_state = LOW;

Bounce debouncer;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  debouncer.attach(button);
  debouncer.interval(5);
}

void loop() {
  debouncer.update();
  if (debouncer.fell())
    led_state = !led_state;

  digitalWrite(led, led_state);
}

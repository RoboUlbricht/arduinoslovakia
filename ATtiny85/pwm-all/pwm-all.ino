/**
  ATtiny85 - PWM on all pins with PWM capability
  v. 1.1
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.5 or higher
  Board: ATtiny85
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
// PWM  (D 4) PB4  3|    |6  PB1 (D 1) PWM
//            GND  4|    |5  PB0 (D 0) PWM
//                  +----+

int pwm_value = 0;
int dms = 20;

void setup() {
  for (int i = 0; i < NUM_DIGITAL_PINS; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  for (int i = 0; i < NUM_DIGITAL_PINS; i++) {
    if (digitalPinHasPWM(i))
      analogWrite(i, pwm_value);
  }

  pwm_value = (pwm_value + 1) % 255;
  delay(dms);
}

/**
  Arduino ATtiny85 TM1637 - ADC
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  Analog reading 0-5 V.

  IDE: 1.8.6 or higher

  Board: ATtiny85
  Core: https://github.com/SpenceKonde/ATTinyCore
  Version: 1.1.5

  TM1637
  https://github.com/avishorp/TM1637
  Version: 1.1.0

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

#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 3

long adc1 = 0;

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x02);
}

void loop() {
  // ADC = ADC1 * 5 V / 1023 (0-5 V)
  // ADC = ADC * 100 {2 decimal places)
  adc1 = analogRead(1) * 500L / 1023;

  // value, decimal dot, no leading zeros
  display.showNumberDecEx(adc1, 0b01000000, false);
  delay(200);
}

/**
  Arduino TM1637 - Leading Zeros
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  Timer with 1000 ms delay.

  IDE: 1.8.6 or higher

  Board: Arduino Uno or Arduino Pro Mini
  Core: https://github.com/arduino/ArduinoCore-avr
  Version: 1.6.22

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
#define CLK 7
#define DIO 6

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   1000
int counter = 0;
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x02);
}

void loop() {
  display.showNumberDec(counter, true);
  counter++;
  delay(TEST_DELAY);
}

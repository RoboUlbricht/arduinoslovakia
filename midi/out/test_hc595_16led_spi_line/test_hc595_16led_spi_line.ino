/**
  Arduino - MIDI sequencer - 2x74HC595 sequence test
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.5 or higher

  Board: Arduino Uno or Arduino Pro Mini
  Core: https://github.com/arduino/ArduinoCore-avr
  Version: 1.6.21

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

#include <SPI.h>

//Pin connected to ST_CP of 74HC595
// SS
int latchPin = 10;

//Pin connected to SH_CP of 74HC595
// SCK
int clockPin = 13;

// Pin connected to DS of 74HC595
// MOSI
int dataPin = 11;

void setup() {
  SPI.begin();
}

void loop() {
  uint16_t data;
  for (int i = 0; i < 16; i++) {
    data = 1 << i;
    digitalWrite(latchPin, LOW);
    SPI.transfer16(data);
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
}




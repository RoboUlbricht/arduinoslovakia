/**
   ATtiny13A Blink
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   3 LED blink.

   IDE: 1.8.1 or higher
   314/1024 bytes of Flash
   5/64 bytes of RAM

   Core:
   https://github.com/MCUdude/MicroCore
     
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

void setup() {
  for (uint8_t i = 0; i < 3; i++)
    pinMode(i, OUTPUT);
}

uint8_t x = 0;

void loop() {
  for (uint8_t i = 0; i < 3; i++)
    digitalWrite(i, x == i ? true : false);
  x++;
  x %= 3;
  delay(1000);
}

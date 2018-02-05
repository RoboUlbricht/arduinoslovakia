/**
   Serial communication between Arduino and Node.js
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Arduino sends. Node.js receives. Arduino simulates crash.
   Node.js closes connection and tries to reopen serial port.

   IDE: 1.8.5 or higher
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

int crash_count = 10;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while(crash_count) {
  Serial.println(millis());
  delay(1000);
  crash_count--;
  }
}


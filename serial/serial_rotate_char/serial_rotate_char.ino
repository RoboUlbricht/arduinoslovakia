/**
   Arduino Serial Rotate
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Rotates char, received from Serial Monitor.

   IDE: 1.8.5
   Board: Arduino Uno

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

int received;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    received = Serial.read();
    switch (received) {
      case '\r':
      case '\n':
        Serial.write(received); // new line is not rotated, we want to see new line in Serial Monitor
        break;
      default:
        Serial.write(received + 1); // char rotate
        break;
    }
  }
}

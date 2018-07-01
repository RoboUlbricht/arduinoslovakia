/**
  Arduino - 4 channel analog test
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

char buffer[30];

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value0 = analogRead(A0);
  int value1 = analogRead(A1);
  int value2 = analogRead(A2);
  int value3 = analogRead(A3);
  sprintf(buffer, "%d,%d,%d,%d", value0, value1, value2, value3);
  Serial.println(buffer);
  delay(100);
}

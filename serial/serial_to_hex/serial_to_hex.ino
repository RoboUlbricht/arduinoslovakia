/**
   Arduino Serial To Hex
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Covert char, received from Serial Monitor, to hexadecimal number.
   Format is in form 'a [61] b [62] c [63] \r [0d] \n [0a]', which uses avrdude
   for debug output.

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
char buffer[20];

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    received = Serial.read();
    switch (received) {
      case '\r':
        sprintf(buffer, "\\r [%02x] ", received);
        Serial.print(buffer);
        break;
      case '\n':
        sprintf(buffer, "\\n [%02x]", received);
        Serial.print(buffer);
        Serial.println();
        break;
      default:
        Serial.write(received);
        sprintf(buffer, " [%02x] ", received);
        Serial.print(buffer);
        break;
    }
  }
}

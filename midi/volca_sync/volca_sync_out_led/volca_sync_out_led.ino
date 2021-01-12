/**
   Arduino Korg Volca Sync Out
   v. 1.0
   Copyright (C) 2021 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Connect LED and resistor 1k to pin 9.
   Connect Korg Volca Sync Out GND to GND.
   Connect Korg Volca Sync Out Left to pin 3.
   https://www.korg.com/us/products/dj/volca_fm/

   IDE: 1.8.12 or higher
   Board: Arduino Pro Micro

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

const int INPUTPIN = 3;
const int LED = 9;

void onChange() {
  digitalWrite(LED, digitalRead(INPUTPIN));
}

void setup() {
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(INPUTPIN), onChange, CHANGE);
}

void loop() {
  // nothing
}

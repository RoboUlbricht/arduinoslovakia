/**
   Arduino Timer2 TCNT2 Simulation
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   This is simulation of what we will get from CTC timer.

   IDE: 1.6.13 or higher
   Board: Arduino Uno or Pro Mini

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
  for (int i = 0; i < 8; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  for (uint8_t i = 0; i <= 255; i++) {
    PORTD = i;
    delay(50);
  }
}

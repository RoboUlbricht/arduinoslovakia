/**
   Schmitt Trigger Oscillator
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Schmitt Trigger Oscillator and visualisation of volatage at control points.

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

// 74HC14 Schmitt Trigger
//
//           +-\/-+
//      1A  1|    |14 Vcc
//      1Y  2|    |13 6A
//      2A  3|    |12 6Y
//      2Y  4|    |11 5A
//      3A  5|    |10 5Y
//      3Y  6|    |9  4A
//      GND 7|    |8  4Y
//           +----+

// Oscillator
// C 10u  - 1A-GND
// R 150k - 1A-1Y

// LED
// Red    - 1Y-R 1k-LED-GND

// Arduino
// A0     - 1A
// A1     - 1Y

const double vref = 5.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  double a0 = analogRead(A0) * vref / 1023.0;
  double a1 = analogRead(A1) * vref / 1023.0;

  Serial.print(a0);
  Serial.print(",");
  Serial.print(a1);
  Serial.println("");
}

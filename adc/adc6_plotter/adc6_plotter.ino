/**
   6x ADC on Plotter
   v. 1.0
   Copyright (C) 2019 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Visualisation of volatagesat control points.

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

const double vref = 5.0;

void setup() {
  Serial.begin(115200);

}

void loop() {
  double a0 = analogRead(A0) * vref / 1023.0;
  double a1 = analogRead(A1) * vref / 1023.0;
  double a2 = analogRead(A2) * vref / 1023.0;
  double a3 = analogRead(A3) * vref / 1023.0;
  double a4 = analogRead(A4) * vref / 1023.0;
  double a5 = analogRead(A5) * vref / 1023.0;

  Serial.print(a0);
  Serial.print(",");
  Serial.print(a1);
  Serial.print(",");
  Serial.print(a2);
  Serial.print(",");
  Serial.print(a3);
  Serial.print(",");
  Serial.print(a4);
  Serial.print(",");
  Serial.print(a5);
  Serial.println("");

  delay(100);
}

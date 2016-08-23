/**
 * MKR1000/Arduino Zero DAC test
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * DAC to ADC test. Connect A0 (DAC) to A1. Use Serial Monitor or
 * Serial Plotter.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

void setup() {
  Serial.begin(9600);
  analogWriteResolution(10);
  analogReadResolution(10);
}

void loop() {
  for(int i=0;i<1024;i++) {
    analogWrite(A0,i);
    int v = analogRead(A1);
    Serial.print(i);
    Serial.print(",");
    Serial.println(v);
    delay(100);
  }
}

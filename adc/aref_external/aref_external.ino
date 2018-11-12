/**
  Arduino TL431 External Voltage Reference
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  TL431 voltage reference (2.5 V) on AREF pin.

  IDE: 1.8.6 or higher

  Board: Arduino Uno or Arduino Pro Mini
  Core: https://github.com/arduino/ArduinoCore-avr
  Version: 1.6.22

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

const double tl431_ref = 2.5;
int value;
double value_v;

void setup() {
  analogReference(EXTERNAL);

  Serial.begin(115200);
  Serial.println("ADC TL431 External reference");
}

void loop() {
  value = analogRead(A0);
  Serial.print("value = ");
  Serial.print(value);
  value_v = value * tl431_ref / 1023;
  Serial.print(", ");
  Serial.print(value_v);
  Serial.println(" V");
  delay(1000);
}

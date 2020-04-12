/**
  Arduino Simple Template Print
  v. 1.0
  Copyright (C) 2020 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.12 or higher
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

template<class T> inline Print& operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

template<> inline Print& operator <<(Print &obj, float arg) {
  obj.print(arg, 3);
  return obj;
}

int cnt = 0;

void setup() {
  Serial.begin(9600);
  Serial << "Simple Template Print\n";
}

void loop() {
  float rnd = random(100000) / 10000.;
  String original(rnd);
  Serial << "Loop: " << cnt << ", " << rnd << " (" << original << ")\n";
  cnt++;
  delay(2000);
}

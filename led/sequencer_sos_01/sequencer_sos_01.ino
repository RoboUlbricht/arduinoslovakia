/**
   Arduino S.O.S.
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Example of typical S.O.S. code.

   Based on
   https://gist.github.com/RedWolves/3824059

   IDE: 1.8.3 or higher
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

int LED = 9;
int s = 300;
int o = 800;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void character(int speed) {
  digitalWrite(LED, HIGH);
  delay(speed);
  digitalWrite(LED, LOW);
  delay(300);
}

void loop() {
  // put your main code here, to run repeatedly: 
  for (int x = 1; x <= 3; x++) {
    character(s);
  }
  delay(100);
  for (int x = 1; x <= 3; x++) {
    character(o);
  }
  delay(100);
  for (int x = 1; x <= 3; x++) {
    character(s);
  }
  delay(2000);
}

/**
   Arduino Uno - Rotary Encoder Debounce
   v. 1.0
   Copyright (C) 2015 Robert Ulbricht
   http://www.arduinoslovakia.eu

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see http://www.gnu.org/licenses/ .
*/

#include <rotary.h>

Rotary r = Rotary(3, 4);
int encoderPosCount = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Rotary Encoder Debounce");
}

void loop() {
  char result = r.process();
  if (result) {
    if (result == DIR_CCW) encoderPosCount--;
    if (result == DIR_CW) encoderPosCount++;

    Serial.print("Rotated: ");
    if (result == DIR_CW) {
      Serial.println("clockwise");
    } else {
      Serial.println("counterclockwise");
    }
    Serial.print("Encoder Position: ");
    Serial.println(encoderPosCount);
  }
}

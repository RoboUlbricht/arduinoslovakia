/**
 * Arduino Uno - Serial Plotter Sinus
 * v. 1.0
 * Copyright (C) 2015 Robert Ulbricht
 * http://www.arduinoslovakia.eu
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
 * along with this program.  If not, see http://www.gnu.org/licenses/ .
 */

#include "math.h"

#define IDE_166
//#define IDE_167

void setup() {
  // Enable Serial Output
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
for (double i = 0; i <= 2*M_PI; i +=2*M_PI/360) {

#if defined(IDE_166)
  Serial.println(sin(i));
#endif

#if defined(IDE_167)
  Serial.print(sin(i));
  Serial.print(",");
  Serial.println(cos(i));
#endif

  delay(10);
  }
}

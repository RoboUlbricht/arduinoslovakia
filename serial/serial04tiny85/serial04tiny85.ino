/**
 * ATtiny85 Serial port test
 * 
 * Copyright (C) 2014 Robert Ulbricht
 *
 * Every second increments number and sends result to
 * serial port.
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

#include <SoftwareSerial.h>

SoftwareSerial s85(0, 1); // RX, TX

int x=0;

void setup() {
  s85.begin(9600);
  s85.println("ATtiny85 Serial test");
}

void loop() {
  x++;
  s85.println(x);
  delay(1000);
}

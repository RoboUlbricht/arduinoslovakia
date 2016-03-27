/**
 * Arduino Uno - MH7400 NAND and AND tester
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
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

/* MH7400
 *  
 *      ---\/---
 *   A1 |01  14| Vcc
 *   B1 |02  13| A4
 *   Y1 |03  12| B4
 *   A2 |04  11| Y4
 *   B2 |05  10| A3
 *   Y2 |06  09| B3
 *  GND |07  08|Y3
 *      --------
 *      
 * Connections:
 * Arduino D10 - A1
 * Arduino D11 - B1
 * Y1=NAND(A1,B1)
 * Y1 - A2
 * Y1 - B2
 * Y2=NOT(Y1) { or Y2=AND(A1,B1) }
 */

const int A=10;
const int B=11;

void setup() {
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
}

struct test {
  int A;
  int B;
} t[]={
  {0,0}, // AND=0, NAND=1
  {0,1}, // AND=0, NAND=1
  {1,0}, // AND=0, NAND=1
  {1,1}  // AND=1, NAND=0
};

void loop() {
  for(int i=0;i<4;i++) {
    digitalWrite(A,t[i].A);
    digitalWrite(B,t[i].B);
    delay(1000);
  }
}

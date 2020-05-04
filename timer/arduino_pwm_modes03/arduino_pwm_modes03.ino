/**
  Arduino PWM modes - Timer1 Fast PWM
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

#include "dump.h"

DREG(TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, RESERVED, RESERVED, WGM11, WGM10)
DREG(TCCR1B, FOC1A, FOC1B, RESERVED, RESERVED, WGM12, CS12, CS11, CS10)
 
void setup() {
  pinMode(9, OUTPUT);  // TIMER1A
  analogWrite(9, 1);   // minimal PWM value
  pinMode(11, OUTPUT); // TIMER2A
  analogWrite(11, 1);  // minimal PWM value

  Serial.begin(9600);
  Serial.println("PWM modes");
  
  // TIMER1
  Serial << _(TCCR1A);
  Serial << _(TCCR1B);
  DUMPVAL(OCR1A)
  DUMPVAL(OCR1B)

  Serial.println("TIMER1 Mode 5: Fast PWM 8-bit");
  TCCR1A = (1 << WGM10) | (1 << COM1A1);
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);
  Serial << _(TCCR1A);
  Serial << _(TCCR1B);
  DUMPVAL(OCR1A)
  DUMPVAL(OCR1B)
}

void loop() {
}

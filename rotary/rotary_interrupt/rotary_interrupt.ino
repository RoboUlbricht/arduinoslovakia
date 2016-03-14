/**
   Arduino Uno - Rotary Encoder Interrupt
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
volatile int encoderPosCount = 0;
volatile char result;
volatile bool signal = false;

ISR(PCINT2_vect)
{
  if(signal)
    return;
  result = r.process();
  if (result) {
    if (result == DIR_CCW) encoderPosCount--;
    if (result == DIR_CW) encoderPosCount++;
    signal = true;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Rotary Encoder Interrupt");

  // pin change interrupt 3, 4
  PCMSK2 |= bit (PCINT19); // want pin 3
  PCMSK2 |= bit (PCINT20); // want pin 4
  PCIFR  |= bit (PCIF2);   // clear any outstanding interrupts
  PCICR  |= bit (PCIE2);   // enable pin change interrupts for D0 to D7
}

void loop() {
  if (signal)
  {
    Serial.print("Rotated: ");
    if (result == DIR_CW) {
      Serial.println("clockwise");
    } else {
      Serial.println("counterclockwise");
    }
    Serial.print("Encoder Position: ");
    Serial.println(encoderPosCount);
    signal = false;
  }
}

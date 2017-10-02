/**
   Orange Pi Zero Blink
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Standard blink.

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

#include <stdio.h>
#include <wiringPi.h>

#define	LED 7

int main (void)
{
  printf ("Orange Pi Zero blink\n");

  wiringPiSetup();
  pinMode(LED, OUTPUT);

  for (;;)
  {
    digitalWrite(LED, HIGH); // On
    delay(500);	             // mS
    digitalWrite(LED, LOW);  // Off
    delay(500);
  }
  return 0;
}

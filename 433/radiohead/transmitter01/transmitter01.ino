/**
   433 MHz communication between Arduinos
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Arduino sends some strings.

   IDE: 1.8.2 or higher
   Board: Arduino Mega

   RadioHead
   v. 1.74
   http://www.airspayce.com/mikem/arduino/RadioHead/

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

#include <RH_ASK.h>

RH_ASK driver;
char buffer[10];
int idx = 0;

void setup()
{
  Serial.begin(9600);	  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  sprintf(buffer, "%d", idx);
  idx++;

  driver.send((uint8_t *)buffer, strlen(buffer));
  driver.waitPacketSent();
  delay(200);
}

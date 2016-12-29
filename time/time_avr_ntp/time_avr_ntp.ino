/**
   Arduino NTP to localtime
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Time conversion.

   IDE: 1.6.13 or higher
   Board: Arduino Uno or Pro Mini
  
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

#include <time.h>

char bufout[256];

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("t = 3688838176; // NTP - Tue Nov 22 21:16:16 2016");
  time_t t = 3688838176; // NTP - Tue Nov 22 21:16:16 2016
 
  // NTP to avr UTC
  Serial.println("t = t - 3155673600L;");
  t = t - 3155673600L;
  
  struct tm _tm;

  // Slovakia timezone
  Serial.println("set_zone(1 * ONE_HOUR);");
  set_zone(1 * ONE_HOUR);

  _tm = *localtime(&t);
  sprintf(bufout, "localtime = %s", asctime(&_tm));
  Serial.println(bufout);
  _tm = *gmtime(&t);
  sprintf(bufout, "gmtime    = %s", asctime(&_tm));
  Serial.println(bufout);
}

void loop() {
}

/**
   Arduino NTP to localtime with daylight saving
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Time conversion test with daylight saving in EU.

   AVR-LIBC: 2.0.0
   Function eu_dst has bugs. For example

   ---
  Mon Feb 29 09:00:00 2016 -  Mon Feb 29 08:00:00 2016
  Tue Mar 01 10:00:00 2016 -  Tue Mar 01 08:00:00 2016
  Wed Mar 02 10:00:00 2016 -  Wed Mar 02 08:00:00 2016
  Thu Mar 03 10:00:00 2016 -  Thu Mar 03 08:00:00 2016
  Fri Mar 04 10:00:00 2016 -  Fri Mar 04 08:00:00 2016
  Sat Mar 05 10:00:00 2016 -  Sat Mar 05 08:00:00 2016
  Sun Mar 06 10:00:00 2016 -  Sun Mar 06 08:00:00 2016
  Mon Mar 07 10:00:00 2016 -  Mon Mar 07 08:00:00 2016
  Tue Mar 08 10:00:00 2016 -  Tue Mar 08 08:00:00 2016
  Wed Mar 09 10:00:00 2016 -  Wed Mar 09 08:00:00 2016
  Thu Mar 10 10:00:00 2016 -  Thu Mar 10 08:00:00 2016
  Fri Mar 11 10:00:00 2016 -  Fri Mar 11 08:00:00 2016
  Sat Mar 12 10:00:00 2016 -  Sat Mar 12 08:00:00 2016
  Sun Mar 13 10:00:00 2016 -  Sun Mar 13 08:00:00 2016
  Mon Mar 14 10:00:00 2016 -  Mon Mar 14 08:00:00 2016
  Tue Mar 15 10:00:00 2016 -  Tue Mar 15 08:00:00 2016
  Wed Mar 16 10:00:00 2016 -  Wed Mar 16 08:00:00 2016
  Thu Mar 17 10:00:00 2016 -  Thu Mar 17 08:00:00 2016
  Fri Mar 18 10:00:00 2016 -  Fri Mar 18 08:00:00 2016
  Sat Mar 19 10:00:00 2016 -  Sat Mar 19 08:00:00 2016
  Sun Mar 20 10:00:00 2016 -  Sun Mar 20 08:00:00 2016
  Mon Mar 21 10:00:00 2016 -  Mon Mar 21 08:00:00 2016
  Tue Mar 22 10:00:00 2016 -  Tue Mar 22 08:00:00 2016
  Wed Mar 23 10:00:00 2016 -  Wed Mar 23 08:00:00 2016
  Thu Mar 24 10:00:00 2016 -  Thu Mar 24 08:00:00 2016
  Fri Mar 25 10:00:00 2016 -  Fri Mar 25 08:00:00 2016
  Sat Mar 26 10:00:00 2016 -  Sat Mar 26 08:00:00 2016
  Sun Mar 27 10:00:00 2016 -  Sun Mar 27 08:00:00 2016
  Mon Mar 28 09:00:00 2016 -  Mon Mar 28 08:00:00 2016
  Tue Mar 29 09:00:00 2016 -  Tue Mar 29 08:00:00 2016
  Wed Mar 30 09:00:00 2016 -  Wed Mar 30 08:00:00 2016
  Thu Mar 31 09:00:00 2016 -  Thu Mar 31 08:00:00 2016
  Fri Apr 01 10:00:00 2016 -  Fri Apr 01 08:00:00 2016
   ---

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
#include <util/eu_dst.h>

char bufout[256];

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // year 2016
  time_t t = (365L * ONE_DAY) * 16 + 8 * ONE_HOUR;
  struct tm _tm;

  // Slovakia timezone
  Serial.println("set_zone(1 * ONE_HOUR);");
  set_zone(1 * ONE_HOUR);
  set_dst(eu_dst);

  for (; t < (365L * ONE_DAY) * 17; t += ONE_DAY)
  {
    _tm = *localtime(&t);
    sprintf(bufout, "%s", asctime(&_tm));
    Serial.print(bufout);
    _tm = *gmtime(&t);
    sprintf(bufout, " -  %s", asctime(&_tm));
    Serial.println(bufout);
  }
}

void loop() {
}

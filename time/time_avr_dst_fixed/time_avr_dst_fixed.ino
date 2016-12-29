/**
   Arduino NTP to localtime with daylight saving
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Time conversion test with daylight saving in EU.

   AVR-LIBC: 2.0.0
   Function eu_dst has bugs. Bugs ar fixed in this replacement.
   http://savannah.nongnu.org/bugs/?44327

   ---
  The function eu_dst(), defined in include/util/eu_dst.h, is intended to
  implement the European daylight saving rules. There is an error at the
  end of the function, where the comparison between the current day of the
  month and the day of the last Sunday is reversed. The error is repeated
  four times. This makes the function be almost always wrong in March and
  October. There is also an off-by-one error earlier in the function:
  whenever the last Sunday is the 25th, the function believes it's the
  32nd.
  I noticed those errors while trying to benchmark my own implementation
  of eu_dst() against the one provided by avr-libc. Then, rather than
  fixing the broken function, I suggest replacing it with my
  implementation:
  int eu_dst(const time_t * timer, int32_t * z)
  {
  uint32_t t = *timer;
  if ((uint8_t)(t >> 24) >= 194) t -= 3029443200U;
  t = (t + 655513200) / 604800 * 28;
  if ((uint16_t)(t % 1461) < 856) return 3600;
  else return 0;
  }
  This version is based on the fact that the European DST function is
  almost periodic. Actually, it is as close to periodic as possible given
  the constraint that the transitions are only allowed on Sundays at 01:00
  UTC. Since this constraint is also periodic, this allows for a compact
  arithmetic solution.
  I tested my implementation for correctness on my PC against the system's
  localtime(), for every full hour between the epoch (2000-01-01) and the
  end of time (2136-02-07). I also tested it on an Arduino Uno
  (ATmega328P) against a precomputed table of all the transition times,
  both at the transition and the second right before.
  In terms of size, this function compiles 52% smaller than the one
  provided by eu_dst.h. If we account for the dependencies, it is 75%
  smaller (204 vs. 826 bytes). It is also 3 times faster:
  about 1250 — 1280 cycles versus 3300 – 4500.
  Regards,
  Edgar Bonet.
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

// fixed version by Edgar Bonet
int eu_dst(const time_t * timer, int32_t * z)
{
  uint32_t t = *timer;
  if ((uint8_t)(t >> 24) >= 194) t -= 3029443200U;
  t = (t + 655513200) / 604800 * 28;
  if ((uint16_t)(t % 1461) < 856) return 3600;
  else return 0;
}

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

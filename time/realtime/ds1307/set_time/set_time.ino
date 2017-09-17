/**
   Arduino DS1307 Set Time
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Write time into DS1307.

   IDE: 1.8.3 or higher
   Board: Arduino Uno, Arduino Pro Mini, Arduino Mega 2560

   Libraries:
   https://github.com/PaulStoffregen/DS1307RTC
   https://github.com/PaulStoffregen/Time

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

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;
bool parse=false;
bool config=false;

void setup() {

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);

  Serial.print("Sketch compile time __TIME__='");
  Serial.print(__TIME__);
  Serial.print("', __DATE__='");
  Serial.print(__DATE__);
  Serial.println("'");

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

  if (parse && config) {
    Serial.println("Parse and write OK.");
  } else if (parse) {
    Serial.println("DS1307 Communication Error");
    Serial.println("Please check your circuitry");
  } else {
    Serial.println("Could not parse info from the compiler");
  }
}

void loop() {
if(parse && config) {
  time_t t=RTC.get();
  Serial.print("RTC.get()=");
  Serial.println(t);
  }
delay(1000);
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}


/**
   Arduino DS1307 Get Time
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Read stored time from DS1307.

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

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Get Time");
  Serial.println("-------------------");
}

void loop() {
  tmElements_t tm;
  time_t t;

  if (RTC.read(tm)) {
    t=makeTime(tm);
    Serial.print("Ok, Time=");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date(D/M/Y)=");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.print(", time_t=");
    Serial.print(t);
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped. Please run the set_time");
      Serial.println("sketch to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error! Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

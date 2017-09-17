/**
   Arduino DS1307 Get RAM
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Read stored data from DS1307.

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

#define DS1307_CTRL_ID 0x68

class DS1307RTCex : public DS1307RTC {
    uint8_t ram[64];

  public:
    DS1307RTCex() : DS1307RTC() {}

    bool readRam() {
      uint8_t *ptr = ram;

      for (uint8_t x = 0; x <= 4; x++) {
        Wire.beginTransmission(DS1307_CTRL_ID);
        Wire.write((uint8_t)x * 16);
        if (Wire.endTransmission() != 0)
          return false;

        uint8_t sz = 16;
        // block
        Wire.requestFrom(DS1307_CTRL_ID, 16);
        if (Wire.available() < 16) return false;
        while (sz) {
          *ptr++ = Wire.read();
          sz--;
        }
      }

      return true;
    }

    void dump() {
      uint8_t nRows = 4;
      char    asciiDump[17];
      int     value;

      for (uint8_t r = 0; r < nRows; r++) {
        uint8_t a = 16 * r;

        Serial.print(F("0x"));
        if ( a < 16 * 16 * 16 ) Serial.print(F("0"));
        if ( a < 16 * 16 ) Serial.print(F("0"));
        if ( a < 16 ) Serial.print(F("0"));
        Serial.print(a, HEX); Serial.print(F(" "));

        for (int c = 0; c < 16; c++) {
          value = ram[a + c];
          if (value < 16)
            Serial.print(F("0"));
          Serial.print(value, HEX);
          Serial.print(c == 7 ? "  " : " ");
          if ((value >= 0x20) && (value < 0x7f))
            asciiDump[c]  = value;
          else
            asciiDump[c]  = '.';
        }
        asciiDump[16] = 0;
        Serial.println(asciiDump);
      }
    }

    void demoRam() {
      uint8_t data = 0;
      for (uint8_t i = 8; i < 64; i++)  {
        Wire.beginTransmission(DS1307_CTRL_ID);
        Wire.write(i);
        Wire.write(data++);
        Wire.endTransmission();
      }
    }

};

DS1307RTCex ex;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Get RAM");
  Serial.println("-------------------");

  //ex.demoRam();

  if (ex.readRam()) {
    ex.dump();
  }
  else
    Serial.println("DS1307RTC Communication error");
}

void loop() {
  delay(1000);
}


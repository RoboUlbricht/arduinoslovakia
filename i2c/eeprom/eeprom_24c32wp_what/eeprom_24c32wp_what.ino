/**
   Read Test of unknown 24C32WP
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   I2C EEPROM. What is hidden inside chip desoldered from dead board?

   IDE: 1.8.2 or higher
   Board: Arduino Pro Mini

   Libraries:
   https://github.com/PaoloP74/extEEPROM

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

#include <extEEPROM.h>

//One 24C32WP EEPROMs on the bus
const uint32_t totalKBytes = 4; // for read and write test functions
extEEPROM eep(kbits_32, 1, 16); 

void setup(void)
{
  Serial.begin(115200);
  uint8_t eepStatus = eep.begin(twiClock400kHz);      //go fast!
  if (eepStatus) {
    Serial.print(F("extEEPROM.begin() failed, status = "));
    Serial.println(eepStatus);
    while (1);
  }

  // dump current EEPROM memory
  dumpEEPROM(0, totalKBytes * 1024);
}

void loop(void)
{
}

// dump eeprom contents, 16 bytes at a time.
// always dumps a multiple of 16 bytes.
void dumpEEPROM(uint32_t startAddr, uint32_t nBytes)
{
  Serial.print(F("EEPROM DUMP 0x"));
  Serial.print(startAddr, HEX);
  Serial.print(F(" 0x"));
  Serial.print(nBytes, HEX);
  Serial.print(F(" "));
  Serial.print(startAddr);
  Serial.print(F(" "));
  Serial.println(nBytes);
  uint32_t nRows = (nBytes + 15) >> 4;

  uint8_t d[16];
  char    asciiDump[17]; 
  
  for (uint32_t r = 0; r < nRows; r++) {
    uint32_t a = startAddr + 16 * r;
    eep.read(a, d, 16);

    Serial.print(F("0x"));
    if ( a < 16 * 16 * 16 ) Serial.print(F("0"));
    if ( a < 16 * 16 ) Serial.print(F("0"));
    if ( a < 16 ) Serial.print(F("0"));
    Serial.print(a, HEX); Serial.print(F(" "));

    for (int c = 0; c < 16; c++) {
      if (d[c] < 16)
        Serial.print(F("0"));
      Serial.print(d[c], HEX);
      Serial.print(c == 7 ? "  " : " ");
      if ((d[c] >= 0x20) && (d[c] < 0x7f))
        asciiDump[c] = d[c];
      else
        asciiDump[c] = '.'; 
    }
    Serial.print(F(" "));
    asciiDump[16] = 0;
    Serial.println(asciiDump); 
  }
}

/**
 * Arduino Uno Debug Dump
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Dump of variables.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

template< typename T > void dumpHex(T &t) {
  int       theValue;
  char      textString[16];
  char      asciiDump[16];
  const uint8_t *myAddressPointer = (uint8_t*) &t;
  int mySize = sizeof(t);
  int maxrow;

  while (mySize > 0) {
    maxrow = min(16, mySize);
    sprintf(textString, "%04X - ", myAddressPointer);
    Serial.print(textString);
    for (int ii = 0; ii < maxrow; ii++) {
      theValue  = *myAddressPointer;
      sprintf(textString, "%02X ", theValue);
      Serial.print(textString);
      if ((theValue >= 0x20) && (theValue < 0x7f))
        asciiDump[ii]  = theValue;
      else
        asciiDump[ii]  = '.';
      myAddressPointer++;
    }
    asciiDump[maxrow] = 0;
    Serial.println(asciiDump);
    mySize -= maxrow;
  }
}

uint8_t sensorAdress[2][8] = {{ 0x28, 0xFF, 0x4E, 0xB8, 0x92, 0x15, 0x1, 0xA4 },
  { 0x28, 0xFF, 0x42, 0xB8, 0x92, 0x15, 0x1, 0x85 },
};

int abc=123;
double xyz=1.;
long qwe=4456789L;
const char mytext[]="ja som text 01234567890123456789";
uint8_t ttt='t';

struct demo {
  int x;
  int y;
  double z;
};

demo strdemo = {1,2,3.2};

#define DUMPVAL(var)     \
 {                       \ 
 Serial.print("Dump: "); \
 Serial.print(#var);     \
 Serial.print("=");      \
 Serial.println(var);    \
 dumpHex(var);           \
 }

#define DUMP(var)        \
 {                       \ 
 Serial.print("Dump: "); \
 Serial.println(#var);   \
 dumpHex(var);           \
 }

void setup() {
  Serial.begin(9600);
  DUMPVAL(abc);
  DUMPVAL(xyz);
  DUMPVAL(qwe);
  DUMP(sensorAdress);
  DUMPVAL(mytext);
  DUMPVAL(ttt);
  DUMP(strdemo);
  DUMPVAL(strdemo.x);
  DUMPVAL(strdemo.y);
  DUMPVAL(strdemo.z);

  for(int i=0;i<3;i++)
    DUMPVAL(i); 
}

void loop() {
}



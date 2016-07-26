/**
 * OHLC Class
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Random values between 0 and 100 into OHLC class.
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

struct OHLCData {
  int o;
  int h;
  int l;
  int c;  
};

const int ohlc_step=10000; // 10 seconds
int value=50;
unsigned long ohlc_next_step;
OHLCData ohlc;

void setup() {
  Serial.begin(9600);
  ohlc_next_step=millis()+ohlc_step;

  ohlc.o=value;
  ohlc.h=value;
  ohlc.l=value;
  ohlc.c=value;
}

void loop() {
  int valuemove=random(3)-1;
  value+=valuemove;
  value=constrain(value,0,100);

  unsigned long m=millis();
  if(m>ohlc_next_step) {
    Serial.print(ohlc.o);
    Serial.print(",");
    Serial.print(ohlc.h);
    Serial.print(",");
    Serial.print(ohlc.l);
    Serial.print(",");
    Serial.print(ohlc.c);
    Serial.println("");
    ohlc.o=value;
    ohlc.h=value;
    ohlc.l=value;
    ohlc.c=value;
    ohlc_next_step+=ohlc_step;
  } else {
    if(ohlc.h<value)
      ohlc.h=value;
    if(ohlc.l>value)
      ohlc.l=value;
    ohlc.c=value;
  }
  delay(100);
}

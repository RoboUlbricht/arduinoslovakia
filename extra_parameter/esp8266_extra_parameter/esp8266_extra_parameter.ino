/**
 * ESP8266 - Extra parameters
 * v. 1.0
 * Copyright (C) 2017 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * IDE: 1.8.2
 * ESP8266 CORE: 2.3.0
 * 
 * Find file 'c:\Users\Robo\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\platform.txt'. 
 * In the same directory create file 'platfom.local.txt'. Insert text 
 * 'compiler.cpp.extra_flags=-DEXTRA_PARAMETER="abc123"' into the file.
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
 * along with this program.  If not, see http://www.gnu.org/licenses/ .
 */
 
#if defined(EXTRA_PARAMETER)
  #define DEPENDENT_PARAMETER "xyz"
#else
  #error EXTRA_PARAMETER not found!
#endif

void setup() {
  Serial.begin(9600);
  while(!Serial)
    ;
  Serial.println(EXTRA_PARAMETER);
  Serial.println(DEPENDENT_PARAMETER);
}

void loop() {
  // nothing
}

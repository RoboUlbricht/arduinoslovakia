/**
   Arduino DS1307 Set SQW Interrupt
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Set Square Wave Output 1Hz.
   Blink with internal LED using interrupt.

   IDE: 1.8.3 or higher
   Board: Arduino Uno, Arduino Pro Mini, Arduino Mega 2560

   Libraries: none

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

#define DS1307_CTRL_ID 0x68
#define ledPin LED_BUILTIN

void setSQW(uint8_t value) {
  Wire.beginTransmission(DS1307_CTRL_ID);
  Wire.write(7);
  Wire.write(value);
  Wire.endTransmission();
}

void handleInt() {
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Set SQW 1 Hz");
  Serial.println("Attach interrupt on D2");
  Serial.println("----------------------");

  pinMode(ledPin,OUTPUT);

  // D2 on Arduino Uno
  // D2 on Arduino Mega 2560
  attachInterrupt(0,handleInt,FALLING);

  // 1Hz
  setSQW(0x10);
}

void loop() {
}


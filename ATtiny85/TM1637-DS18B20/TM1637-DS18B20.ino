/**
  Arduino ATtiny85 TM1637 - DS18B20 Thermometer
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  Simple thermometer.

  IDE: 1.8.6 or higher

  Board: ATtiny85
  Core: https://github.com/SpenceKonde/ATTinyCore
  Version: 1.1.5

  TM1637
  https://github.com/avishorp/TM1637
  Version: 1.1.0

  OneWire
  https://github.com/PaulStoffregen/OneWire
  Version: 2.3.4

  DallasTemperature
  https://github.com/milesburton/Arduino-Temperature-Control-Library
  Version: 3.8.0

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

// ATMEL ATTINY85
//
//                  +-\/-+
//      (D 5) PB5  1|    |8  Vcc
//  DIO (D 3) PB3  2|    |7  PB2 (D 2) temp
//  CLK (D 4) PB4  3|    |6  PB1 (D 1)
//            GND  4|    |5  PB0 (D 0)
//                  +----+

////////////////////////////////////////////////
// Warning: Disconnect PB2 before programming //
////////////////////////////////////////////////

#include <TM1637Display.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 3
#define ONE_WIRE_BUS 2

const uint8_t SEG_ERR[] = {
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, // E
  SEG_E | SEG_G,                         // r
  SEG_E | SEG_G,                         // r
  0,                                     // space
};

TM1637Display display(CLK, DIO);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  display.setBrightness(0x02);
  sensors.begin();
  if (sensors.getDS18Count() == 0)
    display.setSegments(SEG_ERR);
  else
    sensors.setResolution(12);
}

void loop() {
  if (sensors.getDS18Count() != 0) {
    sensors.requestTemperatures();
    double temp = sensors.getTempCByIndex(0);
    display.showNumberDecEx(temp * 100, 0b01000000, false);
  }
  delay(1000);
}

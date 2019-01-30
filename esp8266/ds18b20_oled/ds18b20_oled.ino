/**
   Arduino ESP8266 OLED 0.9 SSD1306 DS18B20 Thermometer
   v. 1.1
   Copyright (C) 2019 Robert Ulbricht
   https://www.arduinoslovakia.eu

   DS18B20 Thermometer.

   IDE: 1.8.6 or higher
   Board: NodeMCU 0.9 (ESP-12)

   Libraries:
   U8g2: https://github.com/olikraus/u8g2
   Version: 2.22.18 or higher

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

#include <U8g2lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D6

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ D1, /* data=*/ D2, /* cs=*/ D5, /* dc=*/ D4, /* reset=*/ D3);
char draw[30];

#define LINE0 11
#define LINE1 22
#define LINE2 33
#define LINE4 44
#define LINE5 55

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_helvR08_tf);

  u8g2.clearBuffer();
  u8g2.drawStr(0, 12, "Arduino Slovakia");
  u8g2.drawStr(0, 26, "DS18B20 Thermometer");
  u8g2.sendBuffer();

  sensors.begin();
  sensors.setResolution(12);

  Serial.begin(115200);

  delay(1000);

  Serial.println("Setup done");
}

void loop() {
  if (sensors.getDS18Count() != 0) {
    sensors.requestTemperatures();
    double temp = sensors.getTempCByIndex(0);
    Serial.println(temp);

    u8g2.clearBuffer();
    sprintf(draw, "Temperature");
    u8g2.setFont(u8g2_font_helvR08_tf);
    u8g2.drawUTF8(1, LINE0, draw);
    sprintf(draw, "%.02f °C", temp);
    u8g2.setFont(u8g2_font_helvB18_tf);
    u8g2.drawUTF8(15, LINE4, draw);
    u8g2.drawFrame(0, 0, 128, 64);
    u8g2.sendBuffer();
  }
  else {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvR08_tf);
    u8g2.drawUTF8(1, LINE0, "Error");
    u8g2.drawFrame(0, 0, 128, 64);
    u8g2.sendBuffer();
  }
  delay(1000);
}

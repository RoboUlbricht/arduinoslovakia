/**
   Arduino ESP8266 OLED 0.9 SSD1306 I2C Scanner
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   I2C Scanner inspired by Raspberry Pi.

   IDE: 1.8.3 or higher
   Board: NodeMCU 0.9 (ESP-12)

   Libraries:
   U8g2: https://github.com/olikraus/u8g2
   Version: 2.9.1 or higher

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
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ D0, /* data=*/ D1, /* cs=*/ D4, /* dc=*/ D3, /* reset=*/ D2);

void setup() {
  Wire.begin(D5, D6);

  delay(300);
  Serial.begin(115200);
  Serial.println("I2C Scanner");

  u8g2.begin();
  u8g2.setFont(u8g2_font_helvB10_tr);
}

void loop() {
  uint8_t error, address, line = 1;
  int nDevices=0;
  char devices[20];
  devices[0] = 0;

  Serial.println("     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
  Serial.print  ("00:         ");

  // https://learn.adafruit.com/i2c-addresses/the-list
  for (address = 0x03; address < 0x78; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      printHex(address);
      sprintf(devices + 3 * nDevices, "%0x ", address);
      nDevices++;
    }
    else if (error == 4)
      Serial.print(" ER");
    else
      Serial.print(" --");

    if ((address + 1) % 16 == 0) {
      Serial.println();
      Serial.print(line);
      Serial.print("0:");
      line++;
    }

  }
  if (nDevices == 0)
    Serial.println("\nNo I2C devices found\n");
  else {
    Serial.print("\nFound ");
    Serial.print(nDevices);
    Serial.println(" devices\n");
  }

  drawFrame(devices);

  delay(5000);           // wait 5 seconds for next scan
}

void drawFrame(const char *devices) {
  u8g2.clearBuffer();
  u8g2.drawStr(0, 14, "I2C Scanner");
  u8g2.drawStr(0, 28, devices);
  u8g2.drawStr(0, 42, "Arduino");
  u8g2.drawStr(0, 56, "Slovakia");
  u8g2.sendBuffer();
}

void printHex(uint8_t address) {
  Serial.print(" ");
  if (address < 16)
    Serial.print("0");
  Serial.print(address, HEX);
}


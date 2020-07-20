/**
  Arduino timer1 10-bit PWM
  v. 1.0
  Copyright (C) 2020 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.12 or higher
  Board: Arduino Pro Mini

  Libraries:
  U8g2: https://github.com/olikraus/u8g2
  Version: 2.27.6 or higher

  OLED | Arduino Pro Mini
  -----|-----------------
  GND  | GND |
  VCC  | VCC |
  CLK  | 13  |
  MOSI | 11  |
  RES  | 8   |
  DC   | 6   |
  CS   | 10  |

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
#include <util/atomic.h>

U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 6, /* reset=*/ 8);

#define ledPin 9

volatile int pwmvalue = 0;
char buff[20];

// Mode 7: 10-bit Fast PWM
void setupTimer1() {
  pinMode(ledPin, OUTPUT);
  TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1A1);
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);
  OCR1A = 1;
}

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);

  setupTimer1();
}

void drawInfo() {
  int y = 12;
  u8g2.firstPage();
  do {

    u8g2.drawStr(0, y, "Arduino Slovakia");
    sprintf(buff, "PWM: %d", pwmvalue);
    u8g2.drawStr(0, y * 3, buff);
  } while ( u8g2.nextPage() );
}

void loop() {
  long v = 0;
  for (int i = 0; i < 64; i++)
    v += analogRead(A0);
  pwmvalue = v / 64;
  OCR1A = pwmvalue;
  drawInfo();
}

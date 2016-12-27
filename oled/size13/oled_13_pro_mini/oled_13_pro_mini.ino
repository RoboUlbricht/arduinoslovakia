/**
   Arduino Pro Mini OLED 1.3 SH1106
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   How to connect OLED display.

   IDE: 1.6.13 or higher
   Board: Arduino Pro Mini

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

U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  //u8g2.setFont(u8g2_font_helvB10_tr);
}

void loop() {
  for (int i = 12; i < 64; i++) {
    drawFrame(i);
    delay(10);
  }
  for (int i = 63; i >= 12; i--) {
    drawFrame(i);
    delay(10);
  }
}

void drawFrame(int y) {
  u8g2.firstPage();
  do {

  u8g2.drawStr(0, y, "Arduino Slovakia"); // write something to the internal memory
  for (int j = 0; j <= 128; j += 2)
    u8g2.drawLine(j, 0, j, (j % 10 == 0 ? 2 : 1));
  for (int j = 0; j <= 64; j += 2)
    u8g2.drawLine(0, j, (j % 10 == 0 ? 2 : 1), j);

  } while ( u8g2.nextPage() );
}


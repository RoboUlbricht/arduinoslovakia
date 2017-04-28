/**
   Arduino Pro Mini OLED 0.9 SSD1306 external EEPROM killer
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Kills 10 bytes of external EEPROM. Be patient. Expect 10-20 mil. of steps.
   1 mil. = 1 hour.

   IDE: 1.8.2 or higher
   Board: Arduino Pro Mini

   Libraries:
   U8g2: https://github.com/olikraus/u8g2 
   Version: 2.14.7 or higher
   
   OLED | Arduino Pro Mini
   -----|-----------------
   GND  | GND | GND
   VCC  | VCC | VCC
   CLK  | 13  | 13
   MOSI | 11  | 11
   RES  | 8   | A1
   DC   | 9   | A2
   CS   | 10  | A3
     
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
#include <extEEPROM.h>

U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ A3, /* dc=*/ A2, /* reset=*/ A1);
char tbuffer[]="t:xxx:xx:xx.xxx";
char sbuffer[]="s:10000000";
char ebuffer[]="e:10/1000000";
unsigned long step=0;
unsigned long errors=0;
int steperrors;
extEEPROM eep(kbits_32, 1, 16);
unsigned char data0[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char data1[] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char d[10];
int datpos=0;

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  uint8_t eepStatus = eep.begin(twiClock400kHz);
  if(eepStatus) {
    while (1);
  }
}

void loop() {
  //eeprom 1st 10 bytes
  steperrors=0;
  eep.write(0, datpos==0 ? data0 : data1, 10);
  eep.read(0,d,10);
  for(int i=0;i<10;i++) {
    unsigned char *data = datpos==0 ? data0 : data1;
    if(d[i]!=data[i]) {
      steperrors++;
      errors++;
    }
  }
  datpos++;
  datpos%=2;

  // update display
  step++;
  if(step%100==0)
    drawFrame();
}

void drawFrame() {
  unsigned long m=millis();
  sprintf(tbuffer,"T:%02d:%02d:%02d.%03d",
          (int)(m/1000L/3600),
          (int)((m/1000L/60)%60),
          (int)((m/1000L)%60),
          (int)(m%1000L));
  sprintf(sbuffer,"S:%07lu",step);
  sprintf(ebuffer,"E:%02d/%07lu",0,errors);
  u8g2.firstPage();
  do {

  u8g2.drawStr(0, 12, tbuffer);
  u8g2.drawStr(0, 24, sbuffer);
  u8g2.drawStr(0, 36, ebuffer);

  } while ( u8g2.nextPage() );
}


/**
   Arduino Pro Mini OLED 0.9 SSD1306 Transistor Blink
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Blink High Power LED using the transistor.

   IDE: 1.8.6 or higher
   Board: Arduino Pro Mini

   Libraries:
   U8g2: https://github.com/olikraus/u8g2 
   Version: 2.27.6 or higher
   TimeOne: https://github.com/PaulStoffregen/TimerOne
   
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
#include <TimerOne.h>

U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

#define ledPin 6
int ledState = LOW;

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);

  pinMode(ledPin, OUTPUT);
  Timer1.initialize(500000); // 500 ms
  Timer1.attachInterrupt(blinkLed);
}

void loop() {
  for (int i = 12; i < 64 - 24; i++) {
    drawFrame(i);
    delay(10);
  }
  for (int i = 63 - 24; i >= 12; i--) {
    drawFrame(i);
    delay(10);
  }
}

void drawFrame(int y) {
  u8g2.firstPage();
  do {

  u8g2.drawStr(0, y, "Arduino Slovakia"); 
  u8g2.drawStr(8, y + 12, "Blink"); 
  u8g2.drawStr(8, y + 24, ledState ? "ON" : "OFF"); 
  for (int j = 0; j <= 128; j += 2)
    u8g2.drawLine(j, 0, j, (j % 10 == 0 ? 2 : 1));
  for (int j = 0; j <= 64; j += 2)
    u8g2.drawLine(0, j, (j % 10 == 0 ? 2 : 1), j);

  } while ( u8g2.nextPage() );
}

void blinkLed(){
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}

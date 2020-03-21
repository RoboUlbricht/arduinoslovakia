/**
  Arduino timer1 led fader
  v. 1.0
  Copyright (C) 2020 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.12 or higher
  Board: Arduino Pro Mini

  Timer calculator
  https://www.arduinoslovakia.eu/application/timer-calculator

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
  DC   | 9   |
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

U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

#define ledPin 6
#define timerStep 10

volatile int divider = 0;
volatile int pwmvalue = 0;
volatile int direction = 1;

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1000 Hz (16000000/((249+1)*64))
  OCR1A = 249;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  
  pinMode(ledPin, OUTPUT);
  setupTimer1();
}

void drawLogo() {
  int y = 12;
  int stp = 14;
  int cpwmvalue;
  int cdirection;
  char prt[10];
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    cpwmvalue = pwmvalue;
    cdirection = direction;
  }
  u8g2.firstPage();
  do {

  u8g2.drawStr(0, y, "Arduino Slovakia"); 
  u8g2.drawStr(0, y + stp * 1, "timer1"); 
  u8g2.drawStr(0, y + stp * 2, "LED fader"); 
  u8g2.drawStr(0, y + stp * 3, cdirection==1 ? "UP" : "DOWN"); 
  sprintf(prt, "%d", cpwmvalue);
  u8g2.drawStr(70, y + stp * 3, prt); 
  } while ( u8g2.nextPage() );
}

void loop() {
  drawLogo();
}

void pwmStep() {
  analogWrite(ledPin, pwmvalue);
  pwmvalue += direction;
  if (pwmvalue == 0)
    direction = 1;
  if (pwmvalue == 255)
    direction = -1;
}

ISR(TIMER1_COMPA_vect) {
  if (divider == 0)
    pwmStep();
  divider++;
  divider %= timerStep;
}

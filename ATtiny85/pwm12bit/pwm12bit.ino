/**
 * ATtiny85 12bit PWM
 * v. 1.0
 * Copyright (C) 2017 Robert Ulbricht
 * https://www.arduinoslovakia.eu
 *
 * Based on http://www.technoblogy.com/show?1NGL
 *          David Johnson-Davies - www.technoblogy.com
 *          Unknown licence (? CC BY 4.0)
 *          
 * Core: https://github.com/SpenceKonde/ATTinyCore
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

// ATMEL ATTINY85
//
//                  +-\/-+
//      (D 5) PB5  1|    |8  Vcc
//      (D 3) PB3  2|    |7  PB2 (D 2)
//      (D 4) PB4  3|    |6  PB1 (D 1) led
//            GND  4|    |5  PB0 (D 0)
//                  +----+ 

volatile int Dac = 0;
volatile int Cycle = 0;

// Overflow interrupt
ISR (TIMER1_OVF_vect) {
  static int remain;
  if (Cycle == 0)
    remain = Dac;
  if (remain >= 256) {
    OCR1A = 255; // high (Table 12-2)
    remain = remain - 256;
  }
  else {
    OCR1A = remain;
    remain = 0;
  }
  Cycle = (Cycle + 1) & 0x0F;
}

void analogWrite10 (int value) {
  cli();
  Dac = value;
  sei();
}

void setup() {
  // Top value for high (Table 12-2)
  OCR1C = 255;
  // Timer/Counter1 doing PWM on OC1A (PB1)
  TCCR1 = 1 << PWM1A    // Pulse Width Modulator A Enable
          | 1 << COM1A0 // OC1x cleared on compare match. Set when TCNT1 = $00
          | 1 << CS10;  // PWM clock = CK
  TIMSK |= 1 << TOIE1; // Timer/Counter1 Overflow Interrupt Enable
  pinMode(1, OUTPUT);
}

void loop () {
  for (int i = 0; i < 100; i++) {
    analogWrite10(i);
    delay(10);
  }
}

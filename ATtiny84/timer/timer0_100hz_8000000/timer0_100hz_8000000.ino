/**
   ATtiny84 Timer0 CTC 1Hz Interrupt Blink
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Blink with interrupts.

   IDE: 1.8.4 or higher
   Board: ATtiny85
   Core: https://github.com/SpenceKonde/ATTinyCore

   AVR Timer CTC Interrupts Calculator
   v. 8
   https://www.arduinoslovakia.eu/application/timer-calculator 

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

#define ledPin 10
volatile int divider=0;

void setupTimer0() {
  noInterrupts();
  // Clear registers
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;

  // 100.16025641025641 Hz (8000000/((77+1)*1024))
  OCR0A = 77;
  // CTC
  TCCR0A |= (1 << WGM01);
  // Prescaler 1024
  TCCR0B |= (1 << CS02) | (1 << CS00);
  // Output Compare Match A Interrupt Enable
  TIMSK0 |= (1 << OCIE0A);
  interrupts();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  setupTimer0();
}

void loop() {
}

ISR(TIMER0_COMPA_vect) {
  if(divider==0)
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  divider++;
  divider%=100;
}

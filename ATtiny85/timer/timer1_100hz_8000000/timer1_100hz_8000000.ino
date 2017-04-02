/**
   ATtiny85 Timer1 CTC 1Hz Interrupt Blink
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Blink with interrupts.

   IDE: 1.8.2 or higher
   Board: ATtiny85
   Core: https://github.com/SpenceKonde/ATTinyCore

   AVR Timer CTC Interrupts Calculator
   v. 6
   http://www.arduinoslovakia.eu/application/timer-calculator 

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

#define ledPin 0
volatile int divider=0;

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCNT1 = 0;
  TCCR1 = 0;

  // 100.16025641025641 Hz (8000000/((155+1)*512))
  OCR1C = 155;
  // interrupt COMPA
  OCR1A = OCR1C;
  // CTC
  TCCR1 |= (1 << CTC1);
  // Prescaler 512
  TCCR1 |= (1 << CS13) | (1 << CS11);
  // Output Compare Match A Interrupt Enable
  TIMSK |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  setupTimer1();
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  if(divider==0)
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  divider++;
  divider%=100;
}

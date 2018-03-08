/**
   ATtiny84 Timer1 CTC 1Hz Interrupt Blink
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

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1 Hz (1000000/((15624+1)*64))
  OCR1A = 15624;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  setupTimer1();
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}

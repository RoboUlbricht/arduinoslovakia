/**
   ATtiny13A Timer0 CTC 1Hz Interrupt Blink
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Blink with interrupts.

   IDE: 1.8.3 or higher
   Board: ATtiny13
   Core: https://github.com/MCUdude/MicroCore

   AVR Timer CTC Interrupts Calculator
   v. 8
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

void setupTimer0() {
  noInterrupts();
  // Clear registers
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;

  // 100.26737967914438 Hz (4800000/((186+1)*256))
  OCR0A = 186;
  // CTC
  TCCR0A |= (1 << WGM01);
  // Prescaler 256
  TCCR0B |= (1 << CS02);
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

ISR(TIM0_COMPA_vect) {
  if(divider==0)
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  divider++;
  divider%=100;
}

/**
   Arduino Mega 2560 Timer5 CTC 1Hz Interrupt Blink
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Blink with interrupts.

   IDE: 1.8.3 or higher
   Board: Arduino Mega 2560

   AVR Timer CTC Interrupts Calculator
   v. 7
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

#define ledPin 13

void setupTimer5() {
  noInterrupts();
  // Clear registers
  TCCR5A = 0;
  TCCR5B = 0;
  TCNT5 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR5A = 15624;
  // CTC
  TCCR5B |= (1 << WGM52);
  // Prescaler 1024
  TCCR5B |= (1 << CS52) | (1 << CS50);
  // Output Compare Match A Interrupt Enable
  TIMSK5 |= (1 << OCIE5A);
  interrupts();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  setupTimer5();
}

void loop() {
}

ISR(TIMER5_COMPA_vect) {
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}

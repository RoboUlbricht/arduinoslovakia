/**
   Arduino Mega 2560 Timer4 CTC 1Hz Interrupt Blink
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

void setupTimer4() {
  noInterrupts();
  // Clear registers
  TCCR4A = 0;
  TCCR4B = 0;
  TCNT4 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR4A = 15624;
  // CTC
  TCCR4B |= (1 << WGM42);
  // Prescaler 1024
  TCCR4B |= (1 << CS42) | (1 << CS40);
  // Output Compare Match A Interrupt Enable
  TIMSK4 |= (1 << OCIE4A);
  interrupts();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  setupTimer4();
}

void loop() {
}

ISR(TIMER4_COMPA_vect) {
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}

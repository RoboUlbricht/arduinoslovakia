/**
   Arduino Timer1 CTC 10Hz Interrupt Animation
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Animation of 8 LEDs with interrupts.

   IDE: 1.6.13 or higher
   Board: Arduino Uno or Pro Mini

   CTC Timer Calculator
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
int counter = 0;

void setupTimer() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 6249; // 10 Hz
  TCCR1A |= 0;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  pinMode(ledPin, OUTPUT);

  for (int i = 2; i < 10; i++)
    pinMode(i, OUTPUT);

  setupTimer();
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);

  for (int i = 0; i < 8; i++)
    digitalWrite(i + 2, i == counter ? true : false);
  counter++;
  counter %= 8;
}

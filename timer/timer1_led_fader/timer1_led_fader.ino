/**
  Arduino timer1 led fader
  v. 1.0
  Copyright (C) 2020 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.12 or higher
  Board: Arduino Pro Mini

  Timer calculator
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
  pinMode(ledPin, OUTPUT);
  setupTimer1();
}

void loop() {
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

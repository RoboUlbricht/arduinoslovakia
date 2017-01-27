/**
   Arduino Timer0 TCNT0 Visualization
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   This is real output from CTC timer0.

   IDE: 1.6.13 or higher
   Board: Arduino Uno or Pro Mini

   AVR Timer CTC Interrupts Calculator
   v. 4
   http://www.arduinoslovakia.eu/application/timer-calculator
   Microcontroller: ATmega328P

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

int divider=0;

void setupTimer() {
  noInterrupts();
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0  = 0;
  
  OCR0A = 155; // 100.16025641025641 Hz
  TCCR0A |= (1 << WGM01);
  TCCR0B |= 0;
  TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
  TIMSK0 |= (1 << OCIE0A);
  interrupts();
}

void setup() {
  pinMode(ledPin, OUTPUT);

  for (int i = 0; i < 8; i++)
    pinMode(i, OUTPUT);
    
  setupTimer();
}

void loop() {
  PORTD = TCNT0;

  // delay replacement, because we changed timer0
  for(long i=0;i<100000;i++)
    __asm__("nop\n"); 
}

ISR(TIMER0_COMPA_vect) {
  if(divider==0)
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  divider++;
  divider%=100;
}

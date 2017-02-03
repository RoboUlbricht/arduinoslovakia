/**
   Arduino Timer1 8x PWM LED
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   8 PWM outputs.

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

#define DIRECT_WRITE
#define FAKE_MAIN

uint8_t counter = 0;
uint8_t light[] = {1, 2, 4, 8, 16, 32, 64, 128};

void setupTimer() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  
  OCR1A = 99; // 20000 Hz
  TCCR1A |= 0;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {

#ifdef DIRECT_WRITE  
  DDRD = 0b11111111;
#else  
  for (uint8_t i = 0; i < 8; i++)
    pinMode(i, OUTPUT);
#endif    
  setupTimer();
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  
#ifdef DIRECT_WRITE
  uint8_t tmp = 0;
  for (uint8_t i = 0; i < 8; i++)
    if(light[i] > counter)
      bitSet(tmp,i);
  PORTD = tmp;    
#else
  for (uint8_t i = 0; i < 8; i++)
    digitalWrite(i, light[i] > counter ? true : false);
#endif

  counter++;
  counter = counter % 255;
}

#ifdef FAKE_MAIN
int main(void) {
  UCSR0B = 0; // disable bootloader USART
  setup();
  while(1)
    loop();
return 0;
}
#endif

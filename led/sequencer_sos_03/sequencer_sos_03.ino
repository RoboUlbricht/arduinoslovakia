/**
   Arduino S.O.S.
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   S.O.S. signal, created by sequencer and timer1.

   Timing based on
   https://gist.github.com/RedWolves/3824059

   IDE: 1.8.3 or higher
   Board: Arduino Pro Mini
   
   AVR Timer CTC Interrupts Calculator
   v. 6
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

#define ledPin 9

// 1 char = 100 ms
const char PROGMEM sequence[] =
  "111000111000111000"
  "0"
  "111111110001111111100011111111000"
  "0"
  "111000111000111000"
  "00000000000000000000";
const int sequence_length = sizeof(sequence)/sizeof(char);

class Sequencer {
  char *data;
  int len;
  int pos;

public:
  Sequencer(char *_data, int _len)
  : data(_data), len(_len), pos(0)
  {}

  void next() {
    char b = pgm_read_byte(&data[pos]); 
    digitalWrite(ledPin,b=='1');
    pos++;
    if(pos==len)
      pos=0;
  }
};

Sequencer seq(sequence,sequence_length);

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 10 Hz (16000000/((6249+1)*256))
  OCR1A = 6249;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 256
  TCCR1B |= (1 << CS12);
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
  seq.next();
}

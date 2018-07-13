/**
  ATtiny85 - Cica Mica against microcontroller
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  3 LED blink.

  IDE: 1.8.5 or higher
  Board: ATtiny85
  Core: https://github.com/SpenceKonde/ATTinyCore

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

// ATMEL ATTINY85
//
//                  +-\/-+
//      (D 5) PB5  1|    |8  Vcc
//      (D 3) PB3  2|    |7  PB2 (D 2) LED3
//      (D 4) PB4  3|    |6  PB1 (D 1) LED2
//            GND  4|    |5  PB0 (D 0) LED1
//                  +----+

// Sequence 1
const char PROGMEM sequence1[] = {
  0b00000001,
  0b00000010,
  0b00000100,
};
const int sequence_length1 = sizeof(sequence1) / sizeof(char);

// Sequence 2
const char PROGMEM sequence2[] = {
  0b00000001,
  0b00000011,
  0b00000010,
  0b00000110,
  0b00000100,
  0b00000101,
};
const int sequence_length2 = sizeof(sequence2) / sizeof(char);

// Sequence 3
const char PROGMEM sequence3[] = {
  0b00000001,
  0b00000010,
  0b00000100,
  0b00000010,
};
const int sequence_length3 = sizeof(sequence3) / sizeof(char);

// Sequence 4
const char PROGMEM sequence4[] = {
  0b00000001,
  0b00000000,
  0b00000001,
  0b00000000,
  0b00000000,
  0b00000010,
  0b00000000,
  0b00000010,
  0b00000000,
  0b00000000,
  0b00000100,
  0b00000000,
  0b00000100,
  0b00000000,
  0b00000000,
  0b00000010,
  0b00000000,
  0b00000010,
  0b00000000,
  0b00000000,
};
const int sequence_length4 = sizeof(sequence4) / sizeof(char);

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
      digitalWrite(0, b & 0b00000001);
      digitalWrite(1, b & 0b00000010);
      digitalWrite(2, b & 0b00000100);
      pos++;
      if (pos == len)
        pos = 0;
    }
};

Sequencer seq1(sequence1, sequence_length1);
Sequencer seq2(sequence2, sequence_length2);
Sequencer seq3(sequence3, sequence_length3);
Sequencer seq4(sequence4, sequence_length4);
enum states {st1, st2, st3, st4, st5, st6, st7};
states state = st1;

void setup() {
  for (uint8_t i = 0; i < 3; i++)
    pinMode(i, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  switch (state) {
    case st1:
      seq1.next();
      delay(80);
      break;
    case st2:
      seq2.next();
      delay(80);
      break;
    case st3:
      seq1.next();
      delay(200);
      break;
    case st4:
      seq2.next();
      delay(200);
      break;
    case st5:
      seq3.next();
      delay(200);
      break;
    case st6:
      seq3.next();
      delay(400);
      break;
    case st7:
      seq4.next();
      delay(200);
      break;
  }
  int r = random(100);
  if (r > 94) {
    state = random(7);
  }
}

/**
   Arduino Traffic Light - Final
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Complete sequence of typical trafic light in Slovakia.
    Pin 2 - Red LED - resistor 1k - GND
    Pin 3 - Yellow LED - resistor 1k - GND
    Pin 4 - Green LED - resistor 1k - GND
    Pin 5 - Red LED - resistor 1k - GND
    Pin 6 - Yellow LED - resistor 1k - GND
    Pin 7 - Green LED - resistor 1k - GND

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

int leds[] = {2, 3, 4, 5, 6, 7};

//  222111xx
//  GYRGYR
const char PROGMEM sequence[] = {
  0b10000100, // red, green
  0b10000100,
  0b10000100,
  0b10000100,
  0b10000100,
  0b10000100,
  0b10000100,
  0b10000100,
  0b10000100,
  0b10000100,
  0b01000100, // red, orange
  0b01000100,
  0b00100100, // red, red
  0b00101100, // red+orange, red
  0b00110000, // green, red
  0b00110000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b00110000,
  0b00101000, // orange, red
  0b00101000,
  0b00100100, // red, red
  0b01100100, // red, red+orange
};
const int sequence_length = sizeof(sequence) / sizeof(char);

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
      PORTD = b;
      pos++;
      if (pos == len)
        pos = 0;
    }
};

Sequencer seq(sequence, sequence_length);

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR1A = 15624;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  for (int i = 0; i < 6; i++)
    pinMode(leds[i], OUTPUT);
  setupTimer1();
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  seq.next();
}

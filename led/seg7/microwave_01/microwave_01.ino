/**
 * Microwave 7 segment display - Numbers
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Numbers from 0-9.
 * 
 * 7 segment display model: SMC-E22E/E30H-UGN
 *  - 13 pins
 *  -- 1-8 - cathodes
 *  -- 9-13 - Anodes
 *  
 *  Position of segments
 *   3
 *  6 2
 *   5
 *  7 1
 *   8
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

uint8_t numbers[]={
  0b11100111, // 0
  0b00000011, // 1
  0b11010110, // 2
  0b10010111, // 3
  0b00110011, // 4
  0b10110101, // 5
  0b11110101, // 6
  0b00000111, // 7
  0b11110111, // 8
  0b10110111, // 9
};

const uint8_t cnt = sizeof(numbers)/sizeof(uint8_t);

// Anodes - 8, 9, 10, 11, 12
const int ANODE = 8;

void setup() {
// cathodes (PORTD)
for(int i=0;i<8;i++)
  pinMode(i,OUTPUT);

// anodes (PORTB)
pinMode(ANODE,OUTPUT);

// turn on 1st digit
digitalWrite(ANODE,HIGH);
}

void loop() {
for(int i=0;i<cnt;i++)
  {
  PORTD=~numbers[i];
  delay(1000);
  }
}

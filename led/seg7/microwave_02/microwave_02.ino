/**
 * Microwave 7 segment display - Arrows
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Arrows.
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

uint8_t arrow[][2]={
  {0b00001000,0b00000001},
  {0b00001000,0b00000010},
  {0b00001000,0b00000100},
  {0b00001000,0b00001000},
  {0b00001000,0b00010000},
  {0b00000001,0b00000100},
  {0b00010000,0b00000100},
  {0b00100000,0b00000100},
  {0b10000000,0b00000100},
  {0b01000000,0b00000100},
};

const uint8_t cnt = sizeof(arrow)/(sizeof(uint8_t)*2);

// Anodes - 8, 9, 10, 11, 12

void setup() {
// cathodes (PORTD)
for(int i=0;i<8;i++)
  pinMode(i,OUTPUT);

// anodes (PORTB)
for(int i=8;i<13;i++)
  pinMode(i,OUTPUT);
}

void loop() {
for(int i=0;i<cnt;i++) {
  PORTB=0;
  PORTB=arrow[i][1];
  PORTD=~arrow[i][0];
  delay(1000);
  }
}

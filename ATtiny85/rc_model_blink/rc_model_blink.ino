/**
 * RC Model Blink
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * 3 LED blink.
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

// ATMEL ATTINY85
//
//                  +-\/-+
//      (D 5) PB5  1|    |8  Vcc
//      (D 3) PB3  2|    |7  PB2 (D 2) led3
//      (D 4) PB4  3|    |6  PB1 (D 1) led2
//            GND  4|    |5  PB0 (D 0) led1
//                  +----+ 

const int led1=0;
const int led2=1;
const int led3=2;

struct pattern {
  long ptime;
  uint8_t value;
};

// 50ms - pattern
// led1
// 10000000000000000000
// led2
// 01000000000000000000
// led3
// 00110000000000000000
//
const pattern p[]= {
  {50,0b001},
  {50,0b010},
  {100,0b100},
  {800,0b000},
};

const int plen=sizeof(p)/sizeof(pattern);

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  for(int i=0;i<plen;i++) {
    const uint8_t &value=p[i].value;
    digitalWrite(led1, value&0b001 ? HIGH : LOW);
    digitalWrite(led2, value&0b010 ? HIGH : LOW);
    digitalWrite(led3, value&0b100 ? HIGH : LOW);
    delay(p[i].ptime);
  }
}

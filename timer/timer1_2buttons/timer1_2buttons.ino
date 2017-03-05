/**
   Arduino Pro Mini OLED 0.9 SSD1306
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   How to connect OLED display.

   IDE: 1.8.1 or higher
   Board: Arduino Pro Mini

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
#define buttonLeft 8
#define buttonRight 6

volatile int value = 0;
int oldvalue = -999;

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
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonLeft,INPUT_PULLUP); // left button
  pinMode(buttonRight,INPUT_PULLUP); // right button
  setupTimer1();
}

void loop() {
  int v;
  noInterrupts();
  v = value;
  interrupts();
  if(v!=oldvalue) {
    Serial.println(v);
    oldvalue = v;
  }
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);

  // left button
  if(digitalRead(buttonLeft)==false) {
    value--;
  }
  // right button
  if(digitalRead(buttonRight)==false) {
    value++;
  }
}

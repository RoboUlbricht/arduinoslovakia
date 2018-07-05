/**
  Arduino - MIDI sequencer - 2x74HC595 + TIMER2 sequence test
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.5 or higher

  Board: Arduino Uno or Arduino Pro Mini
  Core: https://github.com/arduino/ArduinoCore-avr
  Version: 1.6.21

  Libraries:
  ShiftPWM: https://github.com/elcojacobs/ShiftPWM
  Version: unknown 
  
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

// sequencer
volatile int step = 15;
volatile int speed = 1;
#define LED_COUNT 16

// timer2
volatile int divider = 0;

// timer1
const int ShiftPWM_latchPin = 10;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 2;

void setupTimer2() {
  noInterrupts();
  // Clear registers
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  // 1000 Hz (16000000/((124+1)*128))
  OCR2A = 124;
  // CTC
  TCCR2A |= (1 << WGM21);
  // Prescaler 128
  TCCR2B |= (1 << CS22) | (1 << CS20);
  // Output Compare Match A Interrupt Enable
  TIMSK2 |= (1 << OCIE2A);
  interrupts();
}

void setup() {
  //Serial.begin(9600);
  setupTimer2();
  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency, maxBrightness);
}

void loop() {
  for (int j = 0; j < LED_COUNT; j++) {
    unsigned char v = (step % 4) ? 16 : 255;
    ShiftPWM.SetOne(j, step == j ? v : 0);
  }
  delay(20);

  int sp = analogRead(A0);
  long bpm = map(sp, 0, 1023, 60, 600);
  noInterrupts();
  speed = 60000L/bpm;
  interrupts();
}

ISR(TIMER2_COMPA_vect) {
  if (divider == 0) {
    step++;
    step %= 16;
  }
  divider++;
  divider %= speed;
}

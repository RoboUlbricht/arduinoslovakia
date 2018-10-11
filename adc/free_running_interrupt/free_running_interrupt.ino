/**
  Arduino Analog Read - Free Running With Interrupt
  v. 1.1
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  Measure voltage without blocking in free running mode.

  IDE: 1.8.6 or higher

  Board: Arduino Uno or Arduino Pro Mini
  Core: https://github.com/arduino/ArduinoCore-avr
  Version: 1.6.22

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

const byte adc_pin = A0; // = 14 (pins_arduino.h)
volatile unsigned long counter = 0;
unsigned long counter_last = 0;

void setup() {
  Serial.begin (115200);
  Serial.println("ADC Auto Trigger");

  ADCSRB = 0; // ADTS[0-2]=0 - Free Running mode
  ADCSRA = bit(ADEN) // Turn ADC on
           | bit(ADATE) // ADC Auto Trigger Enable
           | bit(ADIE) // Enable interrupt
           | bit(ADPS0) | bit(ADPS1) | bit(ADPS2); // Prescaler of 128
  ADMUX  = bit(REFS0) // AVCC
           | ((adc_pin - 14) & 0x07); // Arduino Uno to ADC pin
  bitSet(ADCSRA, ADSC);
}

void loop() {
  uint8_t SREG_old = SREG;
  noInterrupts();
  unsigned long cnt = counter;
  SREG = SREG_old;
  
  Serial.print("adc_value = ");
  Serial.print(ADC);
  Serial.print(", counter = ");
  Serial.print(cnt);
  Serial.print(" (+");
  Serial.print(cnt - counter_last);
  Serial.println(")");
  counter_last = cnt;
  delay(1000);
}

// ADC complete ISR
ISR(ADC_vect) {
  counter++;
}

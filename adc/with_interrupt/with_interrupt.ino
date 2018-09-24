/**
  Arduino Analog Read With Interrupt
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  Measure voltage without blocking.

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
volatile int adc_value;
volatile bool adc_done;
volatile bool adc_busy;
unsigned int something_different = 0;

void setup() {
  Serial.begin (115200);
  Serial.println("ADC with interrupt");

  ADCSRA = bit(ADEN) // Turn ADC on
           | bit(ADIE) // Enable interrupt
           | bit(ADPS0) | bit(ADPS1) | bit(ADPS2); // Prescaler of 128
  ADMUX  = bit(REFS0) // AVCC
           | ((adc_pin - 14) & 0x07); // Arduino Uno to ADC pin
}

// ADC complete ISR
ISR(ADC_vect) {
  adc_value = ADC;
  adc_done = true;
  adc_busy = false;
}

void loop() {
  // Last reading
  if (adc_done) {
    Serial.print("adc_value=");
    Serial.print(adc_value);
    Serial.print(", something_different=");
    Serial.println(something_different);
    delay(500);
    adc_done = false;
  }

  // Start new conversion
  if (!adc_busy) {
    adc_busy = true;
    // start the conversion
    bitSet(ADCSRA, ADSC);
  }

  // Do something
  something_different++;
}

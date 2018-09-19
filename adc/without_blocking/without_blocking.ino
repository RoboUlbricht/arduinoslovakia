/**
  Arduino Analog Read Without Blocking
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

const byte adcPin = A0; // = 14 (pins_arduino.h)

bool adc_conversion_working = false;

void setup() {
  Serial.begin(115200);
  Serial.println("ADC without blocking");

  ADCSRA = bit(ADEN) // Turn ADC on
           | bit(ADPS0) | bit(ADPS1) | bit(ADPS2); // Prescaler of 128
  ADMUX  = bit(REFS0) // AVCC
           | ((adcPin - 14) & 0x07); // Arduino Uno to ADC pin
}

void loop() {
  if (!adc_conversion_working) {
    bitSet(ADCSRA, ADSC);  // Start a conversion
    adc_conversion_working = true;
  }

  // The ADC clears the bit when done
  if (bit_is_clear(ADCSRA, ADSC)) {
    int value = ADC;  // Read result
    adc_conversion_working = false;
    Serial.println(value);
    delay(500);
  }
}

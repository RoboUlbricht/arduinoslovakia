/**
   Arduino 16-bit PWM
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Based on
   https://arduino.stackexchange.com/questions/12718/increase-pwm-bit-resolution

   Timer1 is set to mode 14 PWM, maximum resolution.
   Connect LED and resistor 1k to pin 9. LED flashes a bit,
   but if the 15-bit resolution is selected, the blinking disappears.

   IDE: 1.8.3 or higher
   Board: Arduino Pro MIni

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

void setup() {
  Serial.begin(9600);
  setupPWM16();
}

uint16_t icr = 0xffff;

void loop() {
  Serial.println("*");
  for (uint16_t i = 0; i < 2000; i++)
  {
    analogWrite16(9, i);
    delay(2);
  }
}

void setupPWM16() {
  DDRB  |= _BV(PB1) | _BV(PB2);       /* set pins as outputs */
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                 /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS10);                  /* prescaler 1 */
  ICR1 = icr;                         /* TOP counter value (freeing OCR1A*/
}

/* Comments about the setup
  Changing ICR1 will effect the amount of bits of resolution.
  ICR1 = 0xffff; (65535) 16-bit resolution
  ICR1 = 0x7FFF; (32767) 15-bit resolution
  ICR1 = 0x3FFF; (16383) 14-bit resolution etc....

  Changing the prescaler will effect the frequency of the PWM signal.
  Frequency[Hz}=CPU/(ICR1+1) where in this case CPU=16 MHz
  16-bit PWM will be>>> 16000000/(65535+1)=244,14Hz
*/

/* 16-bit version of analogWrite(). Works only on pins 9 and 10. */
void analogWrite16(uint8_t pin, uint16_t val)
{
  switch (pin) {
    case  9: OCR1A = val; break;
    case 10: OCR1B = val; break;
  }
}

/**
   Arduino interactive 16-bit PWM
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Based on
   https://arduino.stackexchange.com/questions/12718/increase-pwm-bit-resolution

   Timer1 is set to mode 14 PWM. You can change resolution and brightness.
   Connect LED and resistor 1k to pin 9. Read the instructions on serial port.

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

uint16_t icr = 0xffff;
String line;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino interactive 16-bit PWM");  
  Serial.println("");  
  Serial.println("Resolution: a-i (8-16 bit)");  
  Serial.println("Value: number 0-65535");  
  OCR1A=0;
  OCR1B=0;
  setupPWM16(16);
}

void loop() {
  if(Serial.available()>0) {
    line=Serial.readString();
    line.trim();
    if(line.length()) {
      Serial.print("Command:");
      Serial.println(line);
      if('a'<=line[0] && line[0]<='i') {
        int resolution = 8 + line[0] - 'a';
        Serial.print("Resolution:");
        Serial.println(resolution);
        setupPWM16(resolution);
      }
      else {
        uint16_t value = line.toInt();
        Serial.print("Value:");
        Serial.println(value);
        analogWrite16(9,value);
      }
    }
  }
}

void setupPWM16(int resolution) {
  switch(resolution) {
    case 16:icr=0xffff;break;
    case 15:icr=0x7fff;break;
    case 14:icr=0x3fff;break;
    case 13:icr=0x1fff;break;
    case 12:icr=0x0fff;break;
    case 11:icr=0x07ff;break;
    case 10:icr=0x03ff;break;
    case  9:icr=0x01ff;break;
    case  8:icr=0x00ff;break;
    default:icr=0x00ff;break;
  }
  DDRB  |= _BV(PB1) | _BV(PB2);       /* set pins as outputs */
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                 /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS11);                  /* prescaler 1 */
  ICR1 = icr;                         /* TOP counter value (freeing OCR1A*/
  Serial.print("ICR1:");
  Serial.println(icr);
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

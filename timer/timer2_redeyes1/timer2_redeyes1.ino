/**
   Arduino Uno - Timer1 - 2x Blink
   v. 1.0
   Copyright (C) 2021 Robert Ulbricht
   https://www.arduinoslovakia.eu

   IDE: 1.8.15
   https://www.arduinoslovakia.eu/2021/8/pes-s-modrymi-ocami?lang=en

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

void setupTimer2() {
  noInterrupts();
  // Clear registers
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  // 200.32051282051282 Hz (16000000/((77+1)*1024))
  OCR2A = 77;
  // CTC
  TCCR2A |= (1 << WGM21);
  // Prescaler 1024
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  // Output Compare Match A Interrupt Enable
  TIMSK2 |= (1 << OCIE2A);
  interrupts();
}

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  setupTimer2();
}

class pwmLed {
    int led;
    int pwm;
    int direction;

  public:
    pwmLed(int _led, int _pwm = 0, int _direction = 1)
      : led(_led), pwm(_pwm), direction(_direction)
    {}

    void Next() {
      pwm += direction;
      analogWrite(led, pwm);
      if (pwm == 255)
        direction = -1;
      if (pwm == 0)
        direction = 1;
    }
};

// synchronous eyes
pwmLed pwm1(9, 0, 1);
pwmLed pwm2(10, 0, 1);

ISR(TIMER2_COMPA_vect) {
  static int divider = 0;
  if (divider == 0) {
    pwm1.Next();
    pwm2.Next();
  }
  divider++;
  divider %= 1;
}

void loop() {
}

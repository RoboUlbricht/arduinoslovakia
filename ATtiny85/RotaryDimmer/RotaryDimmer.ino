/**
 * Rotary Encoder Demo
 * v. 1.0
 * Copyright (C)
 *  David Johnson-Davies - www.technoblogy.com - 3rd October 2015
 *  Robert Ulbricht - www.arduinoslovakia.eu
 *
 * Rotary encoder sets PWM on pin 0.
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

// ATtiny85 inputs/outputs
const int LED = 0;
const int EncoderA = 1;
const int EncoderB = 2;
const int EncoderSwitch = 3;

// ATMEL ATTINY85
//
//                      +-\/-+
//          (D 5) PB5  1|    |8  Vcc
// y        (D 3) PB3  2|    |7  PB2 (D 2) b
//          (D 4) PB4  3|    |6  PB1 (D 1) a
// x,c            GND  4|    |5  PB0 (D 0) led
//                      +----+ 

// ROTARY ENCODER
//                      +----+
//                     x|    |a
//             button   |    |c  rotary
//                     y|    |b
//                      +----+

// table of exponential values
// generated for values of i from 0 to 255 -> x=round( pow( 2.0, i/32.0) - 1);
const byte table[] PROGMEM = {
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,
  2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,
  3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,   5,
  5,   5,   5,   5,   5,   5,   5,   6,   6,   6,   6,   6,   6,   6,   7,   7,
  7,   7,   7,   8,   8,   8,   8,   8,   9,   9,   9,   9,   9,  10,  10,  10,
 10,  11,  11,  11,  11,  12,  12,  12,  12,  13,  13,  13,  14,  14,  14,  15,
 15,  15,  16,  16,  16,  17,  17,  18,  18,  18,  19,  19,  20,  20,  21,  21,
 22,  22,  23,  23,  24,  24,  25,  25,  26,  26,  27,  28,  28,  29,  30,  30,
 31,  32,  32,  33,  34,  35,  35,  36,  37,  38,  39,  40,  40,  41,  42,  43,
 44,  45,  46,  47,  48,  49,  51,  52,  53,  54,  55,  56,  58,  59,  60,  62,
 63,  64,  66,  67,  69,  70,  72,  73,  75,  77,  78,  80,  82,  84,  86,  88,
 90,  91,  94,  96,  98, 100, 102, 104, 107, 109, 111, 114, 116, 119, 122, 124,
127, 130, 133, 136, 139, 142, 145, 148, 151, 155, 158, 161, 165, 169, 172, 176,
180, 184, 188, 192, 196, 201, 205, 210, 214, 219, 224, 229, 234, 239, 244, 250
};

// Global - lamp brightness
volatile int Brightness = 3*16;

#define LINEAR_BRIGHTNESS

// Pin change interrupt service routine
ISR (PCINT0_vect) {
  static int Laststate = 0;
  int Gray = (PINB & (1<<EncoderA | 1<<EncoderB))>>EncoderA; // Read PB1 and PB2
  int State = (Gray>>1) ^ Gray;              // Convert from Gray code to binary
  if (State != Laststate) {
    int Value = ((Laststate-State) & 3) - 2; // Gives -1 or +1
    ChangeValue(Value);
    Laststate=State;
  } else
    ChangeSwitch((PINB & 1<<EncoderSwitch)>>EncoderSwitch);     // Gives 0 or 1
  GIFR = 1<<PCIF;                       // Clear pin change interrupt flag.
}

// Called when encoder switch is pressed; On is 0 (down) or 1 (up)
void ChangeSwitch (int On) {
  int b = On ? Brightness : Brightness/2;
  #if defined(LINEAR_BRIGHTNESS)
  b = pgm_read_byte(&table[b]);
  #endif
  analogWrite(0, b);
}

// Called when encoder is rotated; Change is -1 (anticlockwise) or 1 (clockwise)
void ChangeValue (int Change) {
  Change = constrain(Change, -1, 1);
  Brightness = constrain(Brightness+Change, 0, 255);
  int b = Brightness;
  #if defined(LINEAR_BRIGHTNESS)
  b = pgm_read_byte(&table[b]);
  #endif
  analogWrite(0, b);
}
  
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderSwitch, INPUT_PULLUP);
  
  ChangeValue(0); // default brightness

  // Configure pin change interrupts on PB1, PB2, and PB3
  PCMSK |= 1<<PCINT1 | 1<<PCINT2 | 1<<PCINT3;
  GIMSK = 1<<PCIE;                // Enable pin change interrupts
  GIFR = 1<<PCIF;                 // Clear pin change interrupt flag.
}

// Everything done under interrupt!
void loop() {
}

/**
 * ATTiny85 PWM LED Dimmer
 * v. 1.2
 * Copyright (C) 2014 Robert Ulbricht
 *
 * Smooth Led ON/OFF controlled with digital pin 1.
 * Use HC-SR501 as signal source.
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

//#define RDEBUG

// pin definitions
const int led = 0;
const int dig = 1;

// states
enum states {stBoot, stDark, stOn, stHold, stOff, stOff30, stHold30};
states state=stBoot;

#if defined RDEBUG
  #include <SoftwareSerial.h>

  const int dig_tx = 3;
  const int dig_rx = 4;
  SoftwareSerial s85(dig_rx, dig_tx); // RX, TX
#endif

// base ON period
const unsigned long pot_value = 2000;
unsigned long dig_last;
int value = 0;
#if defined RDEBUG
  const unsigned long hold_value = 5*1000L;
#else
  // base hold period
  const unsigned long hold_value = 45*1000L;
#endif

// ATMEL ATTINY85
//
//                      +-\/-+
//          (D 5) PB5  1|    |8  Vcc
// (dig_tx) (D 3) PB3  2|    |7  PB2 (D 2) 
//          (D 4) PB4  3|    |6  PB1 (D 1) dig
//                GND  4|    |5  PB0 (D 0) led
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

///
/// Setup ports
///
void setup() {                
  pinMode(led, OUTPUT); 
  pinMode(dig, INPUT); 
#if defined RDEBUG
  s85.begin(9600);
  s85.println(F("ATtiny85 LED dimmer"));
#else
  for(int i=0;i<2;i++)
    ShowLedIsLive();
#endif
state=stDark;
}

///
/// Test of LEDs functionality
///
void ShowLedIsLive()
{
digitalWrite(led, HIGH); 
delay(200);
digitalWrite(led, LOW); 
delay(200);  
}

///
/// Slow increasing of intensity
///
void LightOn()
{
#if defined RDEBUG
  s85.println(F("Light ON"));
#endif
unsigned long ms=millis();
unsigned long m=0;
unsigned long m2=pot_value;
while(m<m2)
  {
  int p=digitalRead(dig);
  int v=map(m,0,m2,value,255);
  //int vm=pgm_read_byte(&table[v]);
  analogWrite(led,v); 
  m=millis()-ms; 
  }
digitalWrite(led, HIGH);
value=255; 
dig_last=millis()+hold_value;
#if defined RDEBUG
  //s85.print(F("dig_last="));
  //s85.println(dig_last);
#endif
state=stHold;
}

///
///  Wait until digital pin is OFF + hold_value
///
void LightHold() {
#if defined RDEBUG
  s85.println(F("Light HOLD"));
#endif
while(millis()<dig_last)
  {
  int p=digitalRead(dig);
  if(p) // still ON
    {
    dig_last=millis()+hold_value;
    #if defined RDEBUG
      //s85.print(F("dig_last="));
      //s85.println(dig_last);
    #endif
    }
  }
state=stOff;
}

///
/// Slow decreasing of intensity
///
void LightOff() {
#if defined RDEBUG
  s85.println(F("Light OFF"));
#endif
unsigned long ms=millis();
unsigned long m=0;
unsigned long m2=pot_value*6; // 6x on period
while(m<m2)
  {
  int p=digitalRead(dig);
  if(p)
    {
    state=stOn;
    #if defined RDEBUG
      s85.print(F("Signal break at "));
      //s85.println(value);
    #endif
    return;
    }
  value=map(m,0,m2,255,0);  
  int vm=pgm_read_byte(&table[value]);
  value=vm;
  analogWrite(led,vm); 
  if(value<20) {
    state=stHold30;
    return;
    }
  m=millis()-ms; 
  }
digitalWrite(led, LOW);
value=0;
#if defined RDEBUG
  s85.println(F("Dark"));
#endif
state=stDark;
}

///
/// Handles darkness
///
void LightDark() {
  int p=digitalRead(dig);
  if(p)
    state=stOn;
}

///
/// Handled dusk
///
void LightHold30() {
#if defined RDEBUG
  s85.println(F("Light HOLD 30"));
#endif
dig_last=millis()+hold_value;
while(millis()<dig_last)
  {
  int p=digitalRead(dig);
  if(p) // still ON
    {
    #if defined RDEBUG
      //s85.print(F("dig_last="));
      //s85.println(dig_last);
    #endif
    state=stOn;
    return;
    }
  }
state=stOff30;
}

///
/// From dusk to darkness
///
void LightOff30() {
#if defined RDEBUG
  s85.println(F("OFF 30"));
#endif
unsigned long ms=millis();
unsigned long m=0;
unsigned long m2=pot_value;
while(m<m2)
  {
  int p=digitalRead(dig);
  if(p)
    {
    state=stOn;
    return;
    }
  int v=map(m,0,m2,value,0);  
  analogWrite(led,v);
  value=v; 
  m=millis()-ms; 
  }
digitalWrite(led, LOW);
value=0;
state=stDark;
}

///
/// Main loop
///
void loop() {
  switch(state) {
    case stDark:
      LightDark();
      break;
    case stOn:
      LightOn();
      break;
    case stHold:
      LightHold();
      break;
    case stOff:
      LightOff();
      break;
    case stHold30:
      LightHold30();
      break;
    case stOff30:
      LightOff30();
      break;
  }
}

/**
 * ATTiny85 PWM LED Dimmer
 * v. 1.4
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

#include "wiring_private.h"
#include <avr/sleep.h>
#include "enums.h"
#include <EEPROM.h>
#include "EEPROMAnything.h"

//#define RDEBUG

// pin definitions
const int led    = 0;
const int dig    = 1;
const int set_up = 3;
const int address= 0;

volatile boolean signal_wdt = 1;

struct cfg {
  char ident[2];
  unsigned long pot_value;
  unsigned long hold_value;
  unsigned long hold_value30;
};

cfg c={{'1','4'},2000L,45*1000L,45*1000L};

unsigned long dig_last;
int value = 0;

// ATMEL ATTINY85
//
//                      +-\/-+
//          (D 5) PB5  1|    |8  Vcc
// set_up   (D 3) PB3  2|    |7  PB2 (D 2) 
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
SetupEeprom();
SetupCfg();

// disable adc
cbi(ADCSRA, ADEN);
setup_watchdog(wdt64ms);

for(int i=0;i<2;i++)
  ShowLedIsLive();
state=stDark;
}

///
/// Load cfg from EEPROM
///
void SetupEeprom()
{
cfg tmp;
EEPROM_readAnything(address,tmp);
if(!(tmp.ident[0]=='1' && tmp.ident[1]=='4'))
  {
  EEPROM_writeAnything(address,c);
  }
else
  {
  c=tmp;
  EEPROM_writeAnything(address,c);
  }  
}

///
/// User setup
///
/// User must set jumper HIGH on pin signal to not setup.
/// User must set jumper LOW on pin signal to start setup.
///
void SetupCfg()
{
boolean vys;
int value;
pinMode(set_up, INPUT);
digitalWrite(set_up, HIGH); // pull-up
//pinMode(4,OUTPUT);
if(digitalRead(set_up)==LOW)
  {
  // 10 seconds
  delay(100); // debounce
  vys=WaitFor(HIGH,10000L,100,400);
  if(!vys)
    {
    // we reset to default values
    c.pot_value=2000;
    c.hold_value=45*1000L;
    c.hold_value30=45*1000L;
    EEPROM_writeAnything(address,c);
    return;
    }
  // maximum value of hold_value is 120 seconds
  delay(100); // debounce
  value=CountSeconds(LOW,120000L);
  if(value>0)
    {
    if(value<10) value=10; // minimum
    if(value>120) value=120; // maximum
    c.hold_value=value*1000L;
    }
    
  // 10 seconds
  delay(100); // debounce
  vys=WaitFor(HIGH,10000L,100,400);
  if(!vys)
    return;
  // maximum value of hold_value30 is 120 seconds
  delay(100); // debounce
  //digitalWrite(4, HIGH);
  value=CountSeconds(LOW,120000L);
  if(value>0)
    {
    if(value<2) value=2; // minimum
    if(value>120) value=120; // maximum
    c.hold_value30=value*1000L;
    }
    
  // 10 seconds
  delay(100); // debounce
  vys=WaitFor(HIGH,10000L,100,400);
  if(vys)
    EEPROM_writeAnything(address,c);
  }
}

///
/// Waiting for signal
///
boolean WaitFor(int value, unsigned long maxtime, int hperiod, int lperiod)
{
unsigned long ms=millis()+maxtime;
while(millis()<ms)
  {
  if(digitalRead(set_up)==value)
    return true;
  digitalWrite(led, HIGH); 
  delay(hperiod);
  digitalWrite(led, LOW); 
  delay(lperiod);
  }
return false; 
}

///
/// Elapsed signal in seconds
///
int CountSeconds(int value, unsigned long maxtime)
{
unsigned long ss=millis();
unsigned long ms=ss+maxtime;
while(millis()<ms)
  {
  if(digitalRead(set_up)==value)
    return (int)((millis()-ss)/1000L);
  digitalWrite(led, HIGH); 
  delay(100);
  digitalWrite(led, LOW); 
  delay(100);
  digitalWrite(led, HIGH); 
  delay(100);
  digitalWrite(led, LOW); 
  delay(700);
  }

return (int)(maxtime/1000L);
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
unsigned long ms=millis();
unsigned long m=0;
unsigned long m2=c.pot_value;
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
dig_last=millis()+c.hold_value;
state=stHold;
}

///
///  Wait until digital pin is OFF + hold_value
///
void LightHold() {
while(millis()<dig_last)
  {
  int p=digitalRead(dig);
  if(p) // still ON
    {
    dig_last=millis()+c.hold_value;
    }
  }
state=stOff;
}

///
/// Slow decreasing of intensity
///
void LightOff() {
unsigned long ms=millis();
unsigned long m=0;
unsigned long m2=c.pot_value*6; // 6x on period
while(m<m2)
  {
  int p=digitalRead(dig);
  if(p)
    {
    state=stOn;
    return;
    }
  value=map(m,0,m2,255,0);  
  int vm=pgm_read_byte(&table[value]); // nonlinear sensitivity of human eyes
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
state=stDark;
}

///
/// Handles darkness
///
void LightDark() {
  int p=digitalRead(dig);
  if(p)
    state=stOn;
  else
    system_sleep();
}

///
/// Handled dusk
///
void LightHold30() {
dig_last=millis()+c.hold_value30;
while(millis()<dig_last)
  {
  int p=digitalRead(dig);
  if(p) // still ON
    {
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
unsigned long ms=millis();
unsigned long m=0;
unsigned long m2=c.pot_value;
int maxvalue=value;
while(m<m2)
  {
  int p=digitalRead(dig);
  if(p)
    {
    state=stOn;
    return;
    }
  int v=map(m,0,m2,maxvalue,0);  
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

///
/// set system into the sleep state 
/// system wakes up when watchdog is timed out
///
void system_sleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
}

///
/// Setup watchdog
///
/// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
/// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
///
void setup_watchdog(wdtimer t) {
  byte bb;
  int ww;
  if(t>wdt8s)
    t=wdt8s;
  bb=t&7; // WDP[2:0]
  if(t>wdt2s)
    sbi(bb,WDP3);
  sbi(bb,WDCE);
  ww=bb;

  cbi(MCUSR,WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  sbi(WDTCR,WDIE);
}

///
/// Watchdog Interrupt Service
///
/// is executed when watchdog timed out
///
ISR(WDT_vect) {
  signal_wdt=1;  // set global flag
}


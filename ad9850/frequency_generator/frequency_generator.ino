/**
 * Arduino Uno - AD9850 Frequency generator
 * v. 1.0
 * Copyright (C) 2015 Robert Ulbricht
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

/*
The circuit:
 * LCD
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5 V and ground   
 * wiper to LCD VO pin (pin 3)
 *
 * AD9850
 * AD9850 GND to GND
 * AD9850 Vcc to +5 V
 * AD9850 W_CLK to digital pin 10
 * AD9850 FQ_UD to digital pin 9
 * AD9850 DATA to digital pin 8
 * AD9850 RESET to digital pin 7
 */

#include <ARDUINO_AD9850.h>
#include <LiquidCrystal.h>
#include "button.h"
#include "wiring_private.h"

const long MIN_FREQUENCY=       0L;
const long MAX_FREQUENCY=10000000L;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
AD9850 device(10,9,8,7);

int pos=0; // digit position
long frequency=1000L; // initial frequency

///
/// Increment/decrement frequency
///
void PlusFrequency(int direc)
{
long old_frequency=frequency;
switch(pos)
  {
  case 0:frequency+=direc*1L;break;  
  case 1:frequency+=direc*10L;break;  
  case 2:frequency+=direc*100L;break;  
  case 3:frequency+=direc*1000L;break;  
  case 4:frequency+=direc*10000L;break;  
  case 5:frequency+=direc*100000L;break;  
  case 6:frequency+=direc*1000000L;break;  
  }
if(frequency<=MIN_FREQUENCY)
  frequency=MIN_FREQUENCY;
if(frequency>MAX_FREQUENCY)
  frequency=MAX_FREQUENCY;
if(old_frequency!=frequency)
  SendFrequency();
}

///
/// Print frequency
///
void PrintFrequency()
{
char s[10];
ultoa(frequency,s,10);
int dl=strlen(s);
lcd.clear();
lcd.print("Freq=");
lcd.setCursor(16-dl, 0);
lcd.print(s);
lcd.setCursor(15-6, 1);
lcd.print(".  .");  
lcd.setCursor(15-pos, 1);
lcd.print("^");  
}

///
/// Send Frequency
///
void SendFrequency()
{
device.osc(frequency,0);  
}

///
/// f=f+X
///
void OnClickUp(Button *b)
{
if(b->pressed) {
  PlusFrequency(+1);
  PrintFrequency();
  }
}

///
/// f=f-X
///
void OnClickDown(Button *b)
{
if(b->pressed) {
  PlusFrequency(-1);
  PrintFrequency();
  }
}

///
/// Cursor to the left
///
void OnClickLeft(Button *b)
{
if(b->pressed) {
  pos=constrain(pos+1,0,6);
  PrintFrequency();
  }  
}

///
/// Cursor to the left
///
void OnClickRight(Button *b)
{
if(b->pressed) {
  pos=constrain(pos-1,0,6);
  PrintFrequency();
  }
}

Button b1(A0,&OnClickUp);
Button b2(A1,&OnClickDown);
Button b3(A2,&OnClickLeft);
Button b4(A3,&OnClickRight);

///
/// Setup
///
void setup()
{
// disable ADC
cbi(ADCSRA, ADEN);

device.init();
device.doReset();

// set up the LCD's number of columns and rows: 
lcd.begin(16, 2);
  
// Print a message to the LCD.
lcd.print("Frequency gen.");
lcd.setCursor(0, 1);
lcd.print("by RUR");
delay(2000);
lcd.clear();

Serial.begin(9600);
Serial.println("AD9850 frequency generator");

SendFrequency();
PrintFrequency();
}

///
/// Main loop
///
void loop()
{
// check if data has been sent from the computer:
if(Serial.available()) {
  long f=Serial.parseInt();
  frequency=f;
  SendFrequency();
  PrintFrequency();
  }
b1.Read();
b2.Read();
b3.Read();
b4.Read();  
}


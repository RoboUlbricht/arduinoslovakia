/**
 * Teensy 3.1/3.2 - LED Rider
 * v. 1.0
 * Copyright (C) 2015 Robert Ulbricht
 * http://www.arduinoslovakia.eu
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
 * along with this program.  If not, see http://www.gnu.org/licenses/ .
 */

/*
 * The circuit:
 * Connect every LED pin to blue LED and 1k resistor and GND.
 * pin --- LED --- resistor 1k --- GND
 * All this pins have PWM.
 */
 
const int led[]={3,4,5,6,9,10,23,22};
const int ledsize=sizeof(led)/sizeof(int);
int pos=0;
int dir=1;

// select algorithm
#define algo_digital
//#define algo_analog1
//#define algo_analog2

// speed in millis (500-slow, 100-normal, 10-fast)
#define spd 100

void setup()
{
for(int i=0;i<ledsize;i++)
  pinMode(led[i], OUTPUT);
}

void loop()                     
{
for(int i=0;i<ledsize;i++)
  {
  // simple moving LED
  #if defined(algo_digital)
  digitalWrite(led[i], i==pos ? HIGH : LOW);
  #endif
  
  // active LED is brighter, inactive LED is lighter
  #if defined(algo_analog1)
  analogWrite(led[i], i==pos ? 40 : 1);
  #endif
  
  // 3 different light intesities
  #if defined(algo_analog2)
  int val=0;
  switch(abs(i-pos))
    {
    case 0: // active
      val=40;break;
    case 1: // one to the left and one to the right
      val=10;break;
    default:// inactive
      val=1;break;
    }  
  analogWrite(led[i], val);
  #endif
  }
  
pos+=dir;
if(pos==0)
  dir=1; // move to the right
if(pos==ledsize-1)
  dir=-1; // move to the left
delay(spd);
}


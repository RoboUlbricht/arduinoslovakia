/**
 * ATTiny85 PWM LED Dimmer
 * v. 1.0
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

// pin definitions
const int led = 0;
const int dig = 1;
// base ON period
const unsigned long pot_value = 2000;
unsigned long dig_last;
// base hold period
const unsigned long hold_value = 30*1000;

// ATMEL ATTINY85
//
//                  +-\/-+
//      (D 5) PB5  1|    |8  Vcc
//      (D 3) PB3  2|    |7  PB2 (D 2) 
//      (D 4) PB4  3|    |6  PB1 (D 1) dig
//            GND  4|    |5  PB0 (D 0) led
//                  +----+ 

///
/// Setup ports
///
void setup() {                
  pinMode(led, OUTPUT); 
  pinMode(dig, INPUT); 
}

///
/// Slow increasing of intensity
///
void LightOn() {
int v=0;
unsigned long ms=millis();
unsigned long m=0;
unsigned long m2=pot_value;
while(m<m2)
  {
  analogWrite(led,map(m,0,m2,0,255)); 
   m=millis()-ms; 
  }
digitalWrite(led, HIGH);  
}

///
///  Wait until digital pin is OFF + hold_value
///
void LightHold() {
while(millis()<dig_last)
  {
  int p=digitalRead(dig);
  if(p) // still ON
    dig_last=millis()+hold_value;
  }
}

///
/// Slow decreasing of intensity
///
void LightOff() {
unsigned long ms=millis();
unsigned long m=0;
unsigned long m2=pot_value*2; // 2x on period
while(m<m2)
  {
  analogWrite(led,map(m,0,m2,255,0)); 
   m=millis()-ms; 
  }
digitalWrite(led, LOW);  
}

///
/// Main loop
///
void loop() {
  int p=digitalRead(dig);
  if(p) {
    dig_last=millis()+hold_value;
    LightOn(); 
    LightHold();
    LightOff();
  }
}



 /**
 * Arduino Mega - Test different clock speed of two Arduinos
 * v. 1.0
 * Copyright (C) 2015 Robert Ulbricht
 *
 * Load blink sketch into both tested Arduinos. Load this sketch
 * into Arduino Mega or Uno. Connect Gnd on tested Arduinos into
 * Gnd on this Arduino. Connect +5 V on tested Arduinos into +5 V
 * on this Arduino.
 * Blink sketch gives you signal on pin 13. Connect first tested
 * Arduino pin 13 into pin 2 on this Arduino. Connect second tested
 * Arduino pin 13 intopin 3 on this Arduino. And watch Serial monitor.
 
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

volatile boolean signal0=false;
volatile boolean signal1=false;
volatile int32_t t0=0;
volatile int32_t t1=0;

void setup() {
Serial.begin(9600); 
Serial.println("Arduino Mega - Test different clock speed of two Arduinos");

// debug output of interrupt registers
//Serial.println(EICRA);
//Serial.println(EICRB);
//Serial.println(EIMSK);

// pin 2 and 3
attachInterrupt(0,int0,RISING);
attachInterrupt(1,int1,RISING);

// debug output of interrupt registers
//Serial.println(EICRA);
//Serial.println(EICRB);
//Serial.println(EIMSK);
}

void loop() {
if(signal0 && signal1)
  {
  // format time
  int32_t mi=millis()/1000;
  int32_t s=mi%60;
  mi/=60;
  int32_t m=mi%60;
  mi/=60;
  if(m<10) Serial.print("0");
  Serial.print(m);
  Serial.print(":");
  if(s<10) Serial.print("0");
  Serial.print(s);
  
  // difference between Arduinos in micros
  Serial.print(",");
  Serial.print(t1-t0);
  Serial.println("");
  signal0=signal1=false;  
  }
delay(100);
}

void int0() {
t0=micros();
signal0=true;
}

void int1() {
t1=micros();
signal1=true;
}


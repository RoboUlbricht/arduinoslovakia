/**
 * ATTiny85 Analog Comparator Read Registers
 * v. 1.0
 * Copyright (C) 2014 Robert Ulbricht
 *
 * Just read all registers to see default values.
 * After loading program try to connect AIN0 to +5V and
 * AIN1 to GND. Try ro switch them and check the register ACSR.ACO.
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

#include <wiring_private.h>
#include <SoftwareSerial.h>

// ATMEL ATTINY85
//
//                  +-\/-+
//      (D 5) PB5  1|    |8  Vcc
//   tx (D 3) PB3  2|    |7  PB2 (D 2)
//   rx (D 4) PB4  3|    |6  PB1 (D 1) AIN1
//            GND  4|    |5  PB0 (D 0) AIN0
//                  +----+ 

const int dig_tx = 3;
const int dig_rx = 4;
SoftwareSerial s85(dig_rx, dig_tx); // RX, TX
const char htable[]="0123456789ABCDEF";

///
/// Convert to hexadecimal string
/// '0x00'
///
void hexa(unsigned char s) {
  int c;
  s85.print("0x");
  c=(s&0xf0)>>4;
  s85.print(htable[c]);
  c=(s&0x0f);
  s85.print(htable[c]);
  s85.println("");
}

///
/// Show value of one bit
///
void show(unsigned char s, unsigned char bt, const char *name) {
  s85.print("  "); 
  s85.print(name); 
  s85.print(s&(1<<bt) ? 1 : 0); 
  s85.println("");
}

///
/// Show all registers
///
void showregisters() {
  s85.print("ADCSRA=");
  hexa(ADCSRA);
  show(ADCSRA,ADEN,"ADEN=");
  
  s85.print("ADCSRB=");
  hexa(ADCSRB);
  show(ADCSRB,ACME,"ACME=");
  
  s85.print("ACSR  =");
  hexa(ACSR);
  show(ACSR,ACD,"ACD=");
  show(ACSR,ACBG,"ACBG=");
  show(ACSR,ACO,"ACO=");
  show(ACSR,ACI,"ACI=");
  show(ACSR,ACIE,"ACIE=");
  show(ACSR,ACIS1,"ACIS1=");
  show(ACSR,ACIS0,"ACIS0=");

  s85.print("ADMUX =");
  hexa(ADMUX);
  show(ADMUX,MUX1,"MUX1=");
  show(ADMUX,MUX0,"MUX0=");

  s85.print("DIDR0 =");
  hexa(DIDR0);
  show(DIDR0,AIN1D,"AIN1D=");
  show(DIDR0,AIN0D,"AIN0D=");  
}

///
/// Setup ports
///
void setup() {                
  s85.begin(9600);
  s85.println("ATTiny85 Analog Comparator Read Registers");
  pinMode(led, OUTPUT);     
}

///
/// Main loop
///
void loop() {
  showregisters();
  s85.println("---------");
  delay(5000);
}

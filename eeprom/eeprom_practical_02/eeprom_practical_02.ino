/**
 * ATtiny85 EEPROM demo
 * v. 1.0
 * Copyright (C) 2015 Robert Ulbricht
 *
 * Practical eeprom demo - If we have random data
 * in EEPROM, we store default value. If we have
 * our stored value, we can read it, modifi it and store in
 * EEPROM. Try push reset buttom few times.
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

#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"

// ATMEL ATTINY85
//
//                      +-\/-+
//          (D 5) PB5  1|    |8  Vcc
// (dig_tx) (D 3) PB3  2|    |7  PB2 (D 2) 
//          (D 4) PB4  3|    |6  PB1 (D 1)
//                GND  4|    |5  PB0 (D 0)
//                      +----+ 

struct cfg {
  char ident[2];
  int minimum;
  int maximum;
};

cfg c={{'T','1'},0,1234};

const int address = 0;

const int dig_tx = 3;
const int dig_rx = 4;
SoftwareSerial s85(dig_rx, dig_tx); // RX, TX

void setup()
{
  s85.begin(9600);
  s85.println("ATtiny85 EEPROM demo");
  
  cfg tmp;
  EEPROM_readAnything(address,tmp);
  if(!(tmp.ident[0]=='T' && tmp.ident[1]=='1'))
    {
    s85.println("Default value");  
    EEPROM_writeAnything(address,c);
    }
  else
    {
    s85.println("EEPROM stored value");  
    c=tmp;
    c.minimum++;
    c.maximum--;
    EEPROM_writeAnything(address,c);
    }
    
s85.print("cfg.minimum=");
s85.println(c.minimum);  
s85.print("cfg.maximum=");
s85.println(c.maximum);  
}

void loop()
{
  
}

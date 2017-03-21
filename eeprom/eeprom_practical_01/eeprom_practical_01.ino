/**
 * Arduino Uno EEPROM demo
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

#include <EEPROM.h>
#include "EEPROMAnything.h"

struct cfg {
  char ident[2];
  int minimum;
  int maximum;
};

cfg c={{'T','1'},0,1234};

const int address = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino Uno EEPROM demo");
  
  cfg tmp;
  EEPROM_readAnything(address,tmp);
  if(!(tmp.ident[0]=='T' && tmp.ident[1]=='1'))
    {
    Serial.println("Default value");  
    EEPROM_writeAnything(address,c);
    }
  else
    {
    Serial.println("EEPROM stored value");  
    c=tmp;
    c.minimum++;
    c.maximum--;
    EEPROM_writeAnything(address,c);
    }
    
Serial.print("cfg.minimum=");
Serial.println(c.minimum);  
Serial.print("cfg.maximum=");
Serial.println(c.maximum);  
}

void loop()
{

  
}

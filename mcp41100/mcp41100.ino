/**
 * Arduino Uno - Digital potentiometer MCP41100-I/P
 * v. 1.0
 * Copyright (C) 2015 Robert Ulbricht
 *
 * MCP41100 (100k) has one channel and is SPI compatible.
 * Channel's pins are labeled
 *  A - connect this to voltage
 *  W - this is the pot's wiper, which changes when you set it
 *  B - connect this to ground.
 *
 * The MPC41100 is SPI-compatible and to command it, you send two bytes, 
 * one with the channel number and one with the resistance value for the
 * channel (0 - 255). There is only one usable channel number 0x11.  
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

// MPC41100 (Arduino)
//
//                        +-\/-+
// (P10 SPI select) CS   1|    |8  Vcc (+5V)
// (P13 SPI SCK)    SCK  2|    |7  PB0 (GND)
// (P11 SPI MOSI)   SI   3|    |6  PW0 (Output)
// (GND)            GND  4|    |5  PA0 (+5V)
//                        +----+ 

#include <SPI.h>

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
// little delay
const int dl=50;
// channel
// watch datasheet, why there is only one usable value
const byte chnl=0x11;

///
/// Initialization
///
void setup() {
  Serial.begin(9600); 
  Serial.println("Arduino Uno - Digital potentiometer MCP41100-I/P"); 
  pinMode (slaveSelectPin, OUTPUT);
  SPI.begin(); 
}

///
/// Main loop
///
void loop() {
  Serial.println("from 0 to 255");
  // change the resistance on this channel from min to max:
  for (int level = 0; level < 256; level++) {
    digitalPotWrite(chnl, level);
    delay(dl);
  }
  
  // wait a second
  delay(1000);
  
  Serial.println("from 255 to 0");
  // change the resistance on this channel from max to min:
  for (int level = 255; level >=0; level--) {
    digitalPotWrite(chnl, level);
    delay(dl);
  }
  
  // wait a second
  delay(1000);
}

///
/// Modify wiper
///
void digitalPotWrite(byte address, byte value) {
  Serial.println(value);
  // take the SS pin low to select the chip
  digitalWrite(slaveSelectPin,LOW);
  //  send in the address and value via SPI
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip
  digitalWrite(slaveSelectPin,HIGH); 
}


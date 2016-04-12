/**
 * Arduino Uno IR remote test
 * v. 1.0
 * Copyright (C) 2014 Robert Ulbricht
 *
 * Receiver test
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

#include <IRremote.h>
#include "irtestdefine.h"

const int RECV_PIN = 11;

///
/// Translation table
///
struct rbl
{
  RButton b;
  long value;
  const char* name;
};

///
/// Translation table
///
rbl rblv[] =
{
  {rbStandby,vSTANDBY,"STANDBY"},
  {rbBTN1   ,vBTN1   ,"BTN1"},
  {rbBTN2   ,vBTN2   ,"BTN2"},
  {rbBTN3   ,vBTN3   ,"BTN3"},
  {rbBTN4   ,vBTN4   ,"BTN4"},
  {rbBTN5   ,vBTN5   ,"BTN5"},
  {rbBTN6   ,vBTN6   ,"BTN6"},
  {rbBTN7   ,vBTN7   ,"BTN7"},
  {rbBTN8   ,vBTN8   ,"BTN8"},
  {rbBTN9   ,vBTN9   ,"BTN9"},
  {rbBTN0   ,vBTN0   ,"BTN0"},
  {rbPLUS10 ,vPLUS10 ,"PLUS10"},
  {rbMINUS10,vMINUS10,"MINUS10"},
  {rbPLUS1  ,vPLUS1   ,"PLUS1"},
  {rbMINUS1 ,vMINUS1  ,"MINUS1"},
};
int RBLN=sizeof(rblv)/sizeof(rbl);

IRrecv irrecv(RECV_PIN);
decode_results results;

///
/// From scancode to enum
///
RButton DecodeValue(long v)
{
for(int i=0;i<RBLN;i++)
  if(rblv[i].value==v)
    return rblv[i].b;
return rbUNKNOWN;
}

///
/// From enum to human name
///
const char* DecodeName(RButton b)
{
for(int i=0;i<RBLN;i++)
  if(rblv[i].b==b)
    return rblv[i].name;
return "UNKNOWN";  
}

///
/// Setup function
///
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Arduino Uno IR remote test");
}

///
/// Main loop
///
void loop() {
  if (irrecv.decode(&results)) {
    Serial.print(results.value, HEX);
    RButton b=DecodeValue(results.value);
    Serial.print(" - ");
    Serial.print(DecodeName(b));
    Serial.println("");
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

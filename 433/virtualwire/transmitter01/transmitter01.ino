/**
   433 MHz communication between Arduinos
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Arduino sends some strings.

   IDE: 1.8.2 or higher
   Board: Arduino Mega

   VirtualWire
   v. 1.27
   http://www.airspayce.com/mikem/arduino/VirtualWire/

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <VirtualWire.h>

char buffer[10];
int idx=0;

void setup()
{
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sprintf(buffer,"%d",idx);
  idx++;
  
  send(buffer);
  //send("Hello!");
  delay(1000);
}

void send (char *message)
{
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.print("Transmited: ");
  Serial.println(message);
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(LED_BUILTIN,LOW);
}

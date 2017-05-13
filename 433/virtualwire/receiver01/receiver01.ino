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

char message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
int last_idx = 0;

void setup()
{
  Serial.begin(9600);

  Serial.println("Device is ready");

  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec

  vw_rx_start(); // Start the receiver
}


void loop()
{
  if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    message[messageLength] = 0;
    Serial.print("Received(");
    Serial.print(messageLength);
    Serial.print("}: ");
    Serial.print(message);
    
    Serial.print(" (");
    int idx=atoi(message);
    Serial.print(idx>last_idx ? "+" : "-");
    Serial.print(idx-last_idx);
    last_idx=idx;
    Serial.print(")");
    Serial.println();
  }
}

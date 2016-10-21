/**
 * Arduino Uno DS18B20 array generator
 * v. 1.1
 * Copyright (C) 2015 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Using this sketch we use prepare array of temperature sensors addresses.
 * Array can be copied into the sketch ds18b20demoarray.ino.
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

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

///
/// setup of paremeters
///
void setup()
{
Serial.begin(9600);
// Start up the library
sensors.begin();

// Grab a count of devices on the wire
int numberOfDevices = sensors.getDeviceCount();

Serial.println("const DeviceAddress da[]={");
// Loop through each device, print out address
for (int i = 0; i < numberOfDevices; i++)
  {
  // Search the wire for address
  if (sensors.getAddress(tempDeviceAddress, i))
    {
    Serial.print("  {");
    for (uint8_t i = 0; i < 8; i++)
      {
      Serial.print("0x");
      if (tempDeviceAddress[i] < 16) Serial.print("0");
      Serial.print(tempDeviceAddress[i], HEX);
      if (i < 7)
        Serial.print(",");
      }
    if (i < numberOfDevices-1)
      Serial.print("}, // sensor ");
    else
      Serial.print("}  // sensor ");
    Serial.print(i, DEC);
    Serial.println("");
    }
  }
Serial.println("};");
Serial.println("");
Serial.println("const int dacount=sizeof(da)/sizeof(DeviceAddress);");
}

///
/// main loop
///
void loop()
{
// nothing to do
}

/**
   Arduino - Node-Red - DS18B20
   v. 1.0
   Copyright (C) 2019 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Sends DS18B20 values into Node-Red.

   IDE: 1.8.6

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

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
   The setup function. We only start the sensors here
*/
void setup(void)
{
  // start serial port
  Serial.begin(9600);

  // Start up the library
  sensors.begin();
  sensors.setResolution(12);
}

/*
   Main function, get and show the temperature
*/
void loop(void)
{
  int numberOfDevices = sensors.getDeviceCount();
  if (numberOfDevices > 0) {
    sensors.requestTemperatures();
    for (int i = 0; i < numberOfDevices; i++) {
      DeviceAddress tempDeviceAddress;
      sensors.getAddress(tempDeviceAddress, i);
      for (uint8_t i = 0; i < 8; i++) {
        if (tempDeviceAddress[i] < 16) Serial.print("0");
        Serial.print(tempDeviceAddress[i], HEX);
      }
      Serial.print(";");
      float t = sensors.getTempCByIndex(0);
      Serial.println(t);
    }
  }


  delay(2000);
}

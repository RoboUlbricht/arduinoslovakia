/**
   Arduino MKR1000 JSON Generator
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   JSON generator.

   IDE: 1.6.12 or higher

   Libraries:
   Arduino JSON library: https://github.com/bblanchon/ArduinoJson
   Version: 5.7.2 or higher

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

#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // wait serial port initialization
  }

  Serial.println("MKR1000 JSON Generator");
  Serial.println();

  StaticJsonBuffer<400> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();

  root["fld_text"] = "gps";
  root["fld_integer"] = 1351824120;
  root["fld_bool"] = true;
  root["fld_float1"] = 4.12345678;
  root["fld_float2"] = double_with_n_digits(4.12345678, 6);

  JsonArray& data = root.createNestedArray("fld_array");
  for (int i = 0; i < 5; i++)
    data.add(i);

  JsonObject &oin = root.createNestedObject("fld_object");
  oin["x"] = 10;
  oin["y"] = 20;

  root.printTo(Serial);

  Serial.println();
  Serial.println("-----");

  root.prettyPrintTo(Serial);
}

void loop() {
  // not used in this example
}

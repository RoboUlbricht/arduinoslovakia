/**
   Arduino MKR1000 JSON Parser
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   JSON parser.

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
#include "dump.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // wait serial port initialization
  }

  Serial.println("MKR1000 JSON Parser");
  Serial.println();

  StaticJsonBuffer<400> jsonBuffer;

  char json[] =
    "{\n"
    "  \"fld_text\": \"gps\",\n"
    "  \"fld_integer\": 1351824120,\n"
    "  \"fld_bool\": true,\n"
    "  \"fld_float1\": 4.12,\n"
    "  \"fld_float2\": 4.123457,\n"
    "  \"fld_null\": 0,\n"
    "  \"fld_array\": [\n"
    "    0,\n"
    "    1,\n"
    "    2,\n"
    "    3,\n"
    "    4\n"
    "  ],\n"
    "  \"fld_object\": {\n"
    "    \"x\": 10,\n"
    "    \"y\": 20\n"
    "  }\n"
    "}";

  Serial.println(json);
  DUMP(json)

  JsonObject& root = jsonBuffer.parseObject(json);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  const char* fld_text = root["fld_text"];
  long fld_integer = root["fld_integer"];
  bool fld_bool = root["fld_bool"];
  float fld_float = root["fld_float2"];
  DUMPVAL(fld_text)
  DUMPVAL(fld_integer)
  DUMPVAL(fld_bool)
  DUMPVAL(fld_float)

  JsonArray& fld_array = root["fld_array"];
  int a[10];
  memset(a,-1,sizeof(a));
  int poc = fld_array.size();
  if(poc<10)
    fld_array.copyTo(a);
  DUMP(a); 

  struct fobj {
    int x;
    int y;
  };
  fobj fld_object;
  fld_object.x = root["fld_object"]["x"];
  fld_object.y = root["fld_object"]["y"];
  DUMP(fld_object)
  DUMPVAL(fld_object.x)
  DUMPVAL(fld_object.y)
}

void loop() {
  // not used in this example
}

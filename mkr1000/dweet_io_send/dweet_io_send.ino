/**
   Arduino MKR1000 dweet.io POST
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   IDE: 1.6.12 or higher

   Libraries:
   WiFi101: https://github.com/arduino-libraries/WiFi101
   Version: 0.11.0 or higher

   Arduino JSON library: https://github.com/bblanchon/ArduinoJson
   Version: 5.7.3 or higher

   ArduinoHttpClient: https://github.com/arduino-libraries/ArduinoHttpClient
   Version: 0.1.1 or higher

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

#include "password.h"
#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

int status = WL_IDLE_STATUS;
const char server[] = "dweet.io";
WiFiClient wifi;
HttpClient client(wifi, server, 80);
int statusCode = 0;
String response;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(1000);
  }
  Serial.println("Connected to wifi");
}

void loop() {
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["light"] = 456+random(10);
  root["temperature"] = 10.4+random(10)/10.;
  root.prettyPrintTo(Serial);
  Serial.println("");

  char data[256];
  root.printTo(data, sizeof(data));
  client.post("/dweet/for/arduino_slovakia_thing", "application/json", data);

  // read the status code and body of the response
  statusCode = client.responseStatusCode();
  response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  delay(10000);
}

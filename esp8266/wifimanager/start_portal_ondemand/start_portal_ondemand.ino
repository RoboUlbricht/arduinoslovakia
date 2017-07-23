/**
   Arduino ESP8266 WiFi Manager
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Start config portal on button push.

   IDE: 1.8.2 or higher
   Board: NodeMCU 0.9 (ESP-12)

   Libraries:
   WifiManager: https://github.com/tzapu/WiFiManager
   Version: 0.12 or higher

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

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define TRIGGER_PIN 0

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(TRIGGER_PIN) == LOW) {
    WiFiManager wifiManager;

    if(!wifiManager.startConfigPortal("ArduinoAP","secret_password") {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again
      ESP.reset();
      delay(5000);
    }
    Serial.println("connected...");
  }
}

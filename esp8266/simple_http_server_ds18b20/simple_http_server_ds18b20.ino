/**
  ESP8266 - Basic HTTP server with ESP8266
  v. 1.1
  Copyright (C) 2019 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.6 or higher
  Board: NodeMCU 0.9 (ESP-12)
  Core: https://github.com/esp8266/Arduino
  Version: 2.5.0

  Libraries:
  OneWire
  https://github.com/PaulStoffregen/OneWire
  Version: 2.3.4

  DallasTemperature
  https://github.com/milesburton/Arduino-Temperature-Control-Library
  Version: 3.8.0

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
#include <ESP8266WebServer.h>
#include <FS.h>
#include "arduino_secret.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D6

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

ESP8266WebServer server(80);

void handleRoot() {
  Serial.println("GET /");
  File f = SPIFFS.open("/index.html", "r");
  if (!f) {
    Serial.println("File '/index.html' open failed.");
    server.send(500, "text/plain", "500: File '/index.html' open failed.");
  }
  else {
    String body = f.readString();
    if (sensors.getDS18Count() == 0) {
      body.replace("{TEMPERATURE}", "<div class=\"alert alert-danger\">ERROR</div>");
    }
    else {
      sensors.requestTemperatures();
      double temp = sensors.getTempCByIndex(0);
      Serial.println(temp);
      String tempt = "<div class=\"alert alert-info\">" + String(temp) + " °C</div>";
      body.replace("{TEMPERATURE}", tempt);
    }
    server.send(200, "text/html", body);
    f.close();

  }
}

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  sensors.begin();
  SPIFFS.begin();

  server.serveStatic("/favicon.png", SPIFFS, "/favicon.png");
  server.on("/", handleRoot);

  server.onNotFound([]() {
    server.send(404, "text/plain", "404: Not Found");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}

/**
  ESP8266 - Basic HTTP server with ESP8266
  v. 1.0
  Copyright (C) 2019 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.6 or higher
  Board: NodeMCU 0.9 (ESP-12)
  Core: https://github.com/esp8266/Arduino
  Version: 2.5.0

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

ESP8266WebServer server(80);

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
  Serial.print("IP address: http://");
  Serial.println(WiFi.localIP());

  SPIFFS.begin();

  server.serveStatic("/", SPIFFS, "/index.html");
  server.serveStatic("/favicon.png", SPIFFS, "/favicon.png");
  server.serveStatic("/single.js", SPIFFS, "/single.js");
  server.serveStatic("/data.json", SPIFFS, "/data.json");
  server.serveStatic("/nautila.jpg", SPIFFS, "/nautila.jpg");
  server.serveStatic("/obscura.jpg", SPIFFS, "/obscura.jpg");
  server.serveStatic("/polara.jpg", SPIFFS, "/polara.jpg");

  server.onNotFound([]() {
    server.send(404, "text/plain", "404: Not Found");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}

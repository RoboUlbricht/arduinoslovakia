/**
  ESP8266 - Basic HTTP server with one page
  v. 1.1
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
#include "arduino_secret.h"

ESP8266WebServer server(80);

const char htmlPage[] PROGMEM = R"=====(
<html>
<head>
<meta http-equiv="content-type" content="text/html;charset=UTF-8">
<title>Hello from HTTP Server ESP8266</title>
<style>
p { text-indent: 30px; margin: 0px; }
</style>
</head>
<body>
    <h1>ESP8266 HTTP Server</h1>
    <p>Hello from ESP8266 HTTP Server.</p>
    <p>Copyright (C) 2019 <a href="https://www.arduinoslovakia.eu">Arduino Slovakia</a>.</p>
</body>
</html>
)====="; 

void handleRoot() {
  Serial.println("GET /");
  server.send(200, "text/html", htmlPage);
}

void setup(void){
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

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

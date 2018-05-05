/**
  ESP8266 -  Weather forecast from https://openweathermap.org/
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.5 or higher

  Board: ESP8266
  Core: https://github.com/esp8266/Arduino
  Version: 2.4.1

  Libraries:
  Arduino JSON library: https://github.com/bblanchon/ArduinoJson
  Version: 5.13.0 or higher

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
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "arduino_secret.h"

const char* host = "api.openweathermap.org";
const int httpsPort = 443;
const char* url = "/data/2.5/weather";
const char* openweathermapid = "3061186"; // Banska Bystrica
const char* openweathermapq = "Banska%20Bystrica"; // Banska Bystrica
const char* openweathermapunits = "metric"; // Celsius

//String param = String(url) +
//               "?id=" + openweathermapid +
//               "&units=" + openweathermapunits +
//               "&APPID=" + APPID;

String param = String(url) +
               "?q=" + openweathermapq +
               "&units=" + openweathermapunits +
               "&APPID=" + APPID;

String line;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to WiFi");
  //Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + param + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");

  line = client.readStringUntil('\n');
  if (line != "HTTP/1.1 200 OK\r") {
    Serial.print("Unexpected response: ");
    Serial.println(line);
    return;
  }

  if (client.find("\r\n\r\n")) {
    DynamicJsonBuffer jsonBuffer(4096);
    JsonObject& root = jsonBuffer.parseObject(client);
    //root.prettyPrintTo(Serial);

    // parsed output
    const char* name = root["name"];
    Serial.print("City: ");Serial.println(name);

    const double temp = root["main"]["temp"];
    char buffer[64];
    sprintf(buffer, "Temperature: %.02f", temp);
    Serial.println(buffer);

    const int humidity = root["main"]["humidity"];
    sprintf(buffer, "Humidity: %d", humidity);
    Serial.println(buffer);

    const int pressure = root["main"]["pressure"];
    sprintf(buffer, "Pressure: %d", pressure);
    Serial.println(buffer);

    const double wind = root["wind"]["speed"];
    sprintf(buffer, "Wind speed: %.02f m/s", wind);
    Serial.println(buffer);

    const char* weather = root["weather"][0]["main"];
    const char* description = root["weather"][0]["description"];
    sprintf(buffer, "Weather: %s (%s)", weather, description);
    Serial.println(buffer);
  }
}

void loop() {
}


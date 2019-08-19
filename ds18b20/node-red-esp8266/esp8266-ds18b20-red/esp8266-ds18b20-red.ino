/**
  ESP8266 - Send DS18B20 temperature to the Node-RED server
  v. 1.0
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

  ArduinoJson
  https://github.com/bblanchon/ArduinoJson
  Version: 6.11.4

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
#include <ESP8266HTTPClient.h>
#include <FS.h>
#include "arduino_secret.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>

#define ONE_WIRE_BUS D6

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

struct RedConfig {
  long timeout;
  unsigned long previous;
  String server;

  RedConfig()
  : timeout(30000), 
    previous(0), 
    server("http://192.168.0.150:1880/sendtemperature") 
    {}
};

RedConfig cfg;

void loadConfig() {
  File f = SPIFFS.open("/config.json", "r");
  if (!f) {
    Serial.println("File '/config.json' open failed.");
    return;
  }

  StaticJsonDocument<256> doc;
  deserializeJson(doc, f);
  cfg.server = (const char*)doc["server"];
  cfg.timeout = doc["timeout"];
  f.close();
  Serial.printf("New config server: %s\n", cfg.server.c_str());
  Serial.printf("New config timeout: %d\n", cfg.timeout);
}

void sendData() {
  if (WiFi.status() == WL_CONNECTED) {
    int numberOfDevices = sensors.getDeviceCount();
    if (numberOfDevices > 0) {
      sensors.requestTemperatures();
      StaticJsonDocument<1024> array;

      for (int i = 0; i < numberOfDevices; i++) {
        DeviceAddress tda;
        sensors.getAddress(tda, i);
        char id[17];
        sprintf(id, "%02X%02X%02X%02X%02X%02X%02X%02X",
                tda[0], tda[1], tda[2], tda[3],
                tda[4], tda[5], tda[6], tda[7]);
        float t = sensors.getTempCByIndex(0);

        JsonObject nested = array.createNestedObject();
        nested["id"] = id;
        nested["value"] = t;
      }
      serializeJson(array, Serial);
      Serial.println("");

      HTTPClient http;
      bool connected = http.begin(cfg.server);
      if (connected) {
        http.addHeader("Content-Type", "application/json");
        String output;
        serializeJson(array, output);
        int httpCode = http.POST(output);
        Serial.print("http.POST=");
        Serial.print(httpCode);
        if (httpCode < 0) {
          Serial.print(" ");
          Serial.print(http.errorToString(httpCode));
        }
        Serial.println("");
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_BAD_REQUEST) {
          String payload = http.getString();
          Serial.println(payload);
        }
      }
      else
        Serial.println("http.begin error");
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
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
  loadConfig();
}

void loop() {
  unsigned long current = millis();
  if (current - cfg.previous >= cfg.timeout) {
    cfg.previous = current;
    digitalWrite(LED_BUILTIN, LOW);
    sendData();
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

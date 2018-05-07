/**
  ESP8266 -  Weather forecast from https://openweathermap.org/
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.5 or higher

  Board: ESP8266
  Core: https://github.com/esp8266/Arduino
  Version: 2.3.0
           2.4.1 - u8g2.begin() causes WiFi connect problem

  Libraries:
  Arduino JSON library: https://github.com/bblanchon/ArduinoJson
  Version: 5.13.0 or higher
  U8g2: https://github.com/olikraus/u8g2
  Version: 2.22.18 or higher

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
#include <U8g2lib.h>
#include "arduino_secret.h"

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ D1, /* data=*/ D2, /* cs=*/ D5, /* dc=*/ D4, /* reset=*/ D3);
enum oledState {oledBoot, oledConnected, oledRequest, oledParsed, oledError};
enum temperatureState {tempTemperature, tempHumidity, tempPressure, tempWind};
int bootCount = 0;
temperatureState tstate = tempTemperature;
int tick = 0;

struct myTemperature {
  double temperature;
  int humidity;
  int pressure;
  double wind;
  char city[64];
};
myTemperature my_temperature;
char buff[64];

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
  delay(10);
  Serial.println();
  Serial.print("connecting to WiFi ");
  Serial.println(ssid);

  u8g2.begin();

  WiFi.mode(WIFI_STA);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
    connectWiFi();
  else
    showTemperature();
}

void connectWiFi() {
  bootCount = 0;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    bootCount++;
    if (bootCount % 25 == 0)
      Serial.println();
    drawFrame(oledBoot);
  }
  drawFrame(oledConnected);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void showTemperature() {
  if (tick % 60 == 0) { // once per 2 minutes
    downloadData();
  }
  tick++;
  drawFrame(oledParsed);
  delay(2000);
  switch (tstate) {
    case tempTemperature:
      tstate = tempHumidity;
      break;
    case tempHumidity:
      tstate = tempPressure;
      break;
    case tempPressure:
      tstate = tempWind;
      break;
    case tempWind:
      tstate = tempTemperature;
      break;
  }
}

void downloadData() {

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    drawFrame(oledError);
    return;
  }

  drawFrame(oledRequest);
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
    drawFrame(oledError);
    return;
  }

  if (client.find("\r\n\r\n")) {
    DynamicJsonBuffer jsonBuffer(4096);
    JsonObject& root = jsonBuffer.parseObject(client);
    //root.prettyPrintTo(Serial);

    // parsed output
    const char* name = root["name"];
    strcpy(my_temperature.city, name);
    Serial.print("City: "); Serial.println(name);

    my_temperature.temperature = root["main"]["temp"];
    //sprintf(buff, "Temperature: %.02f", my_temperature.temperature);
    dtostrf(my_temperature.temperature, 2, 2, buff);
    Serial.print("Temperature: ");
    Serial.println(buff);

    my_temperature.humidity = root["main"]["humidity"];
    sprintf(buff, "Humidity: %d", my_temperature.humidity);
    Serial.println(buff);

    my_temperature.pressure = root["main"]["pressure"];
    sprintf(buff, "Pressure: %d", my_temperature.pressure);
    Serial.println(buff);

    my_temperature.wind = root["wind"]["speed"];
    //sprintf(buff, "Wind speed: %.02f m/s", my_temperature.wind);
    dtostrf(my_temperature.wind, 2, 1, buff);
    strcat(buff, " m/s");
    Serial.print("Wind speed: ");
    Serial.println(buff);

    const char* weather = root["weather"][0]["main"];
    const char* description = root["weather"][0]["description"];
    sprintf(buff, "Weather: %s (%s)", weather, description);
    Serial.println(buff);
  }

}

void drawFrame(oledState state) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  switch (state) {
    case oledBoot:
      sprintf(buff, "boot(%d)...", bootCount);
      u8g2.drawStr(0, 32, buff);
      break;
    case oledConnected:
      sprintf(buff, "connected...");
      u8g2.drawStr(0, 32, buff);
      break;
    case oledRequest:
      sprintf(buff, "request...");
      u8g2.drawStr(0, 32, buff);
      break;
    case oledParsed:
      switch (tstate) {
        case tempTemperature:
          sprintf(buff, "Temperature");
          u8g2.drawStr(0, 12, buff);
          u8g2.drawStr(0, 62, my_temperature.city);
          //sprintf(buff, "%.02f", my_temperature.temperature);
          dtostrf(my_temperature.temperature, 2, 2, buff);
          strcat(buff, " C");
          u8g2.setFont(u8g2_font_ncenB18_tr);
          u8g2.drawStr(0, 44, buff);
          break;
        case tempHumidity:
          sprintf(buff, "Humidity");
          u8g2.drawStr(0, 12, buff);
          u8g2.drawStr(0, 62, my_temperature.city);
          sprintf(buff, "%d %%", my_temperature.humidity);
          u8g2.setFont(u8g2_font_ncenB18_tr);
          u8g2.drawStr(0, 44, buff);
          break;
        case tempPressure:
          sprintf(buff, "Pressure");
          u8g2.drawStr(0, 12, buff);
          u8g2.drawStr(0, 62, my_temperature.city);
          sprintf(buff, "%d hpa", my_temperature.pressure);
          u8g2.setFont(u8g2_font_ncenB18_tr);
          u8g2.drawStr(0, 44, buff);
          break;
        case tempWind:
          sprintf(buff, "Wind");
          u8g2.drawStr(0, 12, buff);
          u8g2.drawStr(0, 62, my_temperature.city);
          //sprintf(buff, "%1.1f m/s", my_temperature.wind);
          dtostrf(my_temperature.wind, 2, 1, buff);
          strcat(buff, " m/s");
          u8g2.setFont(u8g2_font_ncenB18_tr);
          u8g2.drawStr(0, 44, buff);
          break;
      }
      break;
  }
  u8g2.sendBuffer();
}


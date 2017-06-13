/**
 * ESP8266 - Extra parameters
 * v. 1.0
 * Copyright (C) 2017 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * IDE: 1.8.2
 * ESP8266 CORE: 2.3.0
 * 
 * Find file 'c:\Users\Robo\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\platform.txt'. 
 * In the same directory create file 'platfom.local.txt'. Insert text 
 * 'compiler.cpp.extra_flags=-D_SSID="xxx" -D_PWD="xxx"' into the file.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/ .
 */
 
#include <ESP8266WiFi.h>

#if defined(_SSID)
const char* ssid     = _SSID;
const char* password = _PWD;
#else
const char* ssid     = "your-ssid";
const char* password = "your-password";
#endif

const char* host = "www.arduinoslovakia.eu";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // This will send the request to the server
  client.print(String("GET / HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");

}

void loop() {
  
}

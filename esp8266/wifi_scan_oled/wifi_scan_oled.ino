/**
   Arduino ESP8266 OLED 0.9 SSD1306 WiFi Scanner
   v. 1.1
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   WiFi Scanner.

   IDE: 1.8.2 or higher
   Board: NodeMCU 0.9 (ESP-12)

   Libraries:
   U8g2: https://github.com/olikraus/u8g2
   Version: 2.15.2 or higher

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

#include "ESP8266WiFi.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ D0, /* data=*/ D1, /* cs=*/ D4, /* dc=*/ D3, /* reset=*/ D2);
char draw[30];
char ssid[30];
char mac[30];

#define LINE0 11
#define LINE1 22
#define LINE2 33
#define LINE4 44
#define LINE5 55

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_helvR08_tr);

  u8g2.clearBuffer();
  u8g2.drawStr(0, 12, "Arduino Slovakia");
  u8g2.drawStr(0, 26, "WiFi Scanner");
  u8g2.sendBuffer();

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  Serial.println("Setup done");
}

void messageBox(const char *message)
{
  Serial.println(message);
  u8g2.clearBuffer();
  u8g2.drawStr(0, 12, message);
  u8g2.sendBuffer();
}

void loop() {
  messageBox("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks(false,true); // false - async, true - hidden networks
  messageBox("scan done");
  if (n == 0)
    messageBox("no networks found");
  else
  {
    sprintf(draw, "%d netw. found", n);
    messageBox(draw);
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(") ");
      Serial.println(getEncryptionType(WiFi.encryptionType(i)));

      // oled
      strcpy(ssid,WiFi.SSID(i).c_str());
      int dl=strlen(ssid);
      if(dl>2) { // hide some details
        ssid[dl-2]='?';
        ssid[dl-1]='?';
      }
      strcpy(mac,WiFi.BSSIDstr(i).c_str());
      dl=strlen(mac);
      if(dl>2) { // hide some details
        mac[dl-2]='?';
        mac[dl-1]='?';
      }
      u8g2.clearBuffer();
      sprintf(draw,"Net: %d/%d",i+1,n);
      u8g2.drawStr(1, LINE0, draw);
      u8g2.drawStr(1, LINE1, ssid);
      u8g2.drawStr(1, LINE2, mac);
      sprintf(draw,"Sig: %d dBm",WiFi.RSSI(i));
      u8g2.drawStr(1, LINE4, draw);
      sprintf(draw,"Ch: %d",WiFi.channel(i));
      u8g2.drawStr(80, LINE4, draw);
      sprintf(draw,"Enc: %s",getEncryptionType(WiFi.encryptionType(i)));
      u8g2.drawStr(1, LINE5, draw);
      u8g2.drawFrame(0,0,128,64);
      u8g2.sendBuffer();
      
      delay(2000);
    }
  }
  Serial.println("");
}

const char S_WEP[] = "WEP";
const char S_TKIP[] = "WPA";
const char S_CCMP[] = "WPA2";
const char S_NONE[] = "None";
const char S_AUTO[] = "Auto";
const char S_UNKNOWN[] = "Unkn.";

const char* getEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      return S_WEP;
    case ENC_TYPE_TKIP:
      return S_TKIP;
    case ENC_TYPE_CCMP:
      return S_CCMP;
    case ENC_TYPE_NONE:
      return S_NONE;
    case ENC_TYPE_AUTO:
      return S_AUTO;
    default:
      return S_UNKNOWN;
  }
}

/**
   Arduino MKR1000 Nokia 5110 Scan Network
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   IDE: 1.6.12 or higher

   Libraries:
   Nokia 5110: https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library
   Version: 1.0.1 or higher

   WiFi101: https://github.com/arduino-libraries/WiFi101
   Version: 0.11.0 or higher

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

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <WiFi101.h>

// Software SPI (slower updates, more flexible pin options):
// pin 1 - Serial clock out (SCLK)
// pin 2 - Serial data out (DIN)
// pin 3 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 5 - LCD reset (RST)
Adafruit_PCD8544 nokia = Adafruit_PCD8544(1, 2, 3, 4, 5);

void setup()   {
  Serial.begin(9600);

  nokia.begin();
  nokia.setContrast(60);
  nokia.clearDisplay();   // clears the screen and buffer
  drawIntro();
  nokia.clearDisplay();
  nokia.display();


  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    nokia.setCursor(0, 0);
    nokia.print("WiFi shield not present");
    nokia.display();
    // don't continue:
    while (true);
  }

  // Print WiFi MAC address:
  printMacAddress();
}

///
/// Intro
///
/// Two pages of text
///
void drawIntro()
{
  nokia.setCursor(0, 0);
  nokia.print("WiFi Scan Network");
  Serial.println("WiFi Scan Network");
  nokia.setCursor(0, 20);
  nokia.print("www.arduinoslovakia.eu");
  nokia.display();
  delay(2000);
  nokia.clearDisplay();
  nokia.setCursor(0, 0);
  nokia.print("List of all WiFi networks.");
  Serial.println("List of all WiFi networks.");
  nokia.display();
  delay(2000);
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];
  char draw[30];

  // print your MAC address:
  WiFi.macAddress(mac);
  sprintf(draw, "MAC:%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);

  nokia.clearDisplay();
  nokia.setCursor(0, 0);
  nokia.print(draw);
  Serial.println(draw);

  nokia.display();
}

void loop() {
  // scan for existing networks:
  Serial.println("Scanning available networks...");
  nokia.clearDisplay();
  nokia.setCursor(0, 0);
  nokia.print("Scanning...");
  nokia.display();
  listNetworks();
}

void listNetworks() {
  char draw[30];
  char ssid[M2M_MAX_SSID_LEN];
  
  // scan for nearby networks:
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("Number of available networks: ");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    strcpy(ssid,WiFi.SSID(thisNet));
    int dl=strlen(ssid);
    if(dl>2) { // hide some details
      ssid[dl-2]='?';
      ssid[dl-1]='?';
    }
    
    Serial.print(thisNet+1);
    Serial.print(") ");
    Serial.print(ssid);
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    Serial.println(getEncryptionType(WiFi.encryptionType(thisNet)));
    Serial.flush();

    nokia.clearDisplay();
    nokia.setCursor(0, 0);
    sprintf(draw,"Net: %d/%d",thisNet+1,numSsid);
    nokia.print(draw);
    nokia.setCursor(0, 8);
    nokia.print(ssid);
    nokia.setCursor(0, 24);
    sprintf(draw,"Sig: %d dBm",WiFi.RSSI(thisNet));
    nokia.print(draw);
    nokia.setCursor(0, 32);
    sprintf(draw,"Enc: %s",getEncryptionType(WiFi.encryptionType(thisNet)));
    nokia.print(draw);
    nokia.display();

    delay(2000);
  }
}

const char S_WEP[]="WEP";
const char S_TKIP[]="WPA";
const char S_CCMP[]="WPA2";
const char S_NONE[]="None";
const char S_AUTO[]="Auto";
const char S_UNKNOWN[]="Unkn.";

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


/**
   Arduino MKR1000 Nokia 5110 Udp NTP Client
   v. 1.0
   Copyright (C) 2016 Robert Ulbricht
   http://www.arduinoslovakia.eu

   Get the time from a Network Time Protocol (NTP) time server
   Demonstrates use of UDP sendPacket and ReceivePacket
   For more on NTP time servers and the messages needed to communicate with them,
   see http://en.wikipedia.org/wiki/Network_Time_Protocol

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
#include <WiFiUdp.h>
#include <time.h>
#include "dump.h"

// Software SPI (slower updates, more flexible pin options):
// pin 1 - Serial clock out (SCLK)
// pin 2 - Serial data out (DIN)
// pin 3 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 5 - LCD reset (RST)
Adafruit_PCD8544 nokia = Adafruit_PCD8544(1, 2, 3, 4, 5);

int status = WL_IDLE_STATUS;
char ssid[] = "XXXX";  // your network SSID (name)
char pass[] = "XXXX";  // your network password

unsigned int localPort = 2390;      // local port to listen for UDP packets
IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
WiFiUDP Udp; // A UDP instance to let us send and receive packets over UDP


void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  nokia.begin();
  nokia.setContrast(60);
  drawIntro();
  nokia.clearDisplay();
  nokia.display();

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    TRACETEXT("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  TRACETEXT("Connected to wifi");
  printWifiStatus();

  TRACETEXT("Starting connection to server...");
  uint8_t res;
  Udp.begin(localPort);
  TRACE1("Udp.begin",res)
}

///
/// Intro
///
/// Two pages of text
///
void drawIntro()
{
  nokia.clearDisplay();
  nokia.setCursor(0, 0);
  nokia.print("Udp NTP Client");
  Serial.println("Udp NTP Client");
  nokia.setCursor(0, 20);
  nokia.print("www.arduinoslovakia.eu");
  nokia.display();
  delay(2000);
  nokia.clearDisplay();
  nokia.setCursor(0, 0);
  nokia.print("Get current time from NTP server.");
  Serial.println("Get current time from NTP server.");
  nokia.display();
  delay(2000);
}

void loop()
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  if ( Udp.parsePacket() ) {
    TRACETEXT("Packet received");
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    DUMP(packetBuffer)

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;

    time_t unixtime = epoch;
    tm *timeinfo;
    timeinfo = gmtime( &unixtime );

    char bufout[256];
    sprintf(bufout, "Unix time = %u is year=%d, month=%d, day=%d, wday=%d, hour=%d, min=%d, sec=%d",
            (unsigned int)unixtime,
            timeinfo->tm_year + 1900,
            timeinfo->tm_mon,
            timeinfo->tm_mday,
            timeinfo->tm_wday,
            timeinfo->tm_hour,
            timeinfo->tm_min,
            timeinfo->tm_sec);
    Serial.println(bufout);
    DUMPVAL(*tzname);

    sprintf(bufout,"asctime = %s",asctime(timeinfo));
    Serial.println(bufout);
    
    sprintf(bufout,"%s",asctime(timeinfo));
    nokia.clearDisplay();
    nokia.setCursor(0, 0);
    nokia.print(bufout);
    nokia.setCursor(0, 24);
    strftime (bufout,80,"%T",timeinfo);
    nokia.print(bufout);
    nokia.setCursor(0, 32);
    strftime (bufout,80,"%F",timeinfo);
    nokia.print(bufout);
    nokia.setCursor(0, 40);
    strftime (bufout,80,"%A",timeinfo);
    nokia.print(bufout);
    nokia.display();
   
  }
  else
    TRACETEXT("Packet lost");
  // wait ten seconds before asking for the time again
  delay(10000);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  TRACEFUNC()
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  int res;
  res=Udp.beginPacket(address, 123); //NTP requests are to port 123
  TRACE1("Udp.beginPacket",res)
  res=Udp.write(packetBuffer, NTP_PACKET_SIZE);
  TRACE1("Udp.write",res)
  res=Udp.endPacket();
  TRACE1("Udp.endPacket",res)
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}











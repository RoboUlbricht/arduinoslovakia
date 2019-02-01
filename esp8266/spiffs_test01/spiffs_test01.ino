/**
   Arduino ESP8266 SPIFFS Info
   v. 1.0
   Copyright (C) 2019 Robert Ulbricht
   https://www.arduinoslovakia.eu

   SPIFFS basic info.

   IDE: 1.8.6 or higher
   Board: NodeMCU 0.9 (ESP-12)

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

#include <FS.h>

void setup() {
  Serial.begin(115200);

  bool res = SPIFFS.begin();
  Serial.print("SPIFFS.begin() = ");
  Serial.println(res);

  if (res) {
    FSInfo fs_info;
    SPIFFS.info(fs_info);

    Serial.print("fs_info.totalBytes = ");
    Serial.println(fs_info.totalBytes);
    Serial.print("fs_info.usedBytes = ");
    Serial.println(fs_info.usedBytes);
    Serial.print("fs_info.blockSize = ");
    Serial.println(fs_info.blockSize);
    Serial.print("fs_info.pageSize = ");
    Serial.println(fs_info.pageSize);
    Serial.print("fs_info.maxOpenFiles = ");
    Serial.println(fs_info.maxOpenFiles);
    Serial.print("fs_info.maxPathLength = ");
    Serial.println(fs_info.maxPathLength);
  }
}

void loop() {
}

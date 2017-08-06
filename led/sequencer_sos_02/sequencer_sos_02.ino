/**
   Arduino S.O.S.
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu

   S.O.S. signal, created by sequencer.

   Timing based on
   https://gist.github.com/RedWolves/3824059

   IDE: 1.8.3 or higher
   Board: Arduino Pro Mini

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

const int LED = 9;
// 1 char = 100 ms
const char PROGMEM sequence[] =
  "111000111000111000"
  "0"
  "111111110001111111100011111111000"
  "0"
  "111000111000111000"
  "00000000000000000000";
const int sequence_length = sizeof(sequence)/sizeof(char);

class Sequencer {
  char *data;
  int len;
  int pos;

public:
  Sequencer(char *_data, int _len)
  : data(_data), len(_len), pos(0)
  {}

  void next() {
    char b = pgm_read_byte(&data[pos]); 
    Serial.print(b);
    digitalWrite(LED,b=='1');
    pos++;
    if(pos%10==0)
      Serial.println("");
    if(pos==len) {
      pos=0;
      Serial.println("");
      Serial.println("-- restart --");
    }
  }
};

Sequencer seq(sequence,sequence_length);

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.print("sequence_length: ");
  Serial.println(sequence_length);
}

void loop() {
  seq.next();
  delay(100);
}

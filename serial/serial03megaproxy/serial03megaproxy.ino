/**
 * Arduino Mega 2560 Serial port proxy test
 * 
 * Copyright (C) 2014 Robert Ulbricht
 *
 * Read from serial port 1, sends result to
 * serial port 0.
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

char buffer[256];
boolean show_length=false;
boolean show_millis=false;
boolean show_hexa=false;
const char htable[]="0123456789ABCDEF";

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Arduino Mega 2560 Serial proxy test");
}

void updateconfig() {
  int c=Serial.read();
  Serial.print("cfg:");
  Serial.println((char)c);
  switch(c) {
    case 'l':show_length=!show_length;
      break;
    case 'm':show_millis=!show_millis;
      break;
    case 'h':show_hexa=!show_hexa;
      break;
  }    
}

void hexa(char *s) {
  int c;
  while(*s) {
    c=(*s&0xf0)>>4;
    Serial.print(htable[c]);
    c=(*s&0x0f);
    Serial.print(htable[c]);
    s++;
    if(*s)
      Serial.print(' ');
  }
  Serial.println("");
}

void loop() {
if(Serial.available()) {
  updateconfig();
  }
  
size_t n=Serial1.readBytesUntil('\n',buffer,255);
buffer[n]=0;
if(n>0) {
  buffer[n-1]=0;
  if(show_length)
    Serial.println(n);
  if(show_hexa)
    hexa(buffer);
  Serial.print("ser1:");
  if(show_millis) {
    Serial.print(millis());
    Serial.print(":");
    }
  Serial.println(buffer);
  }
}

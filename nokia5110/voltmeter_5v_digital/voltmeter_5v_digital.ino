/**
 * Nokia 5110 Voltmeter 5V Digital
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * 4 channel voltmeter.
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

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

struct VoltmeterData {
  const int channel;
  const char name[3];
  double value;
};

VoltmeterData data[4]={
  {A0,"A0",0.},
  {A1,"A1",0.},
  {A2,"A2",0.},
  {A3,"A3",0.},
};

char buffer[10];
const double vref=5.0;
const int samples=8;

void setup() {
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  display.display();
}

void loop() {
  measure(samples);
  drawVoltmeter();
  delay(200);
}

void measure(const int smp) {
  long d;
  for(int i=0;i<4;i++) {
    d=0;
    for(int x=0;x<smp;x++)
      d+=analogRead(data[i].channel);
    data[i].value= d * vref / 1023.0 / smp;
  }  
}

void drawVoltmeter() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Voltmeter");
  display.setCursor(0,8);
  display.print("Range: 0-5 V");
  for(int i=0;i<4;i++) {
    display.setCursor(0,8*i+16);
    display.print(data[i].name);

    display.setCursor(30,8*i+16);
    dtostrf(data[i].value, 4, 3, buffer);
    display.print(buffer);
    display.print(" V");
  }
  display.display();
}



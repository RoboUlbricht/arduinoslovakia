 /**
 * Arduino Nokia 5110 Interrupt Counter
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Counts interrupts on Arduino Uno pin 2.
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

volatile boolean signal0=false;
volatile int32_t t0=0;

const int type=RISING;
//const int type=FALLING;
//const int type=CHANGE;

void drawDisplay() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Interrupt");
  display.setCursor(0,8);
  display.print("Counter");

  display.setCursor(0,32);
  display.print("MS: ");
  display.print(millis());
  display.setCursor(0,40);
  display.print("CNT: ");
  display.print(t0);
  display.display();
  
}

void setup() {
  display.begin();
  display.setContrast(60);
  drawDisplay();
  
  Serial.begin(9600); 
  Serial.println("Arduino Interrupt Counter");
  switch(type)
    {
    case RISING:  Serial.println("Type: RISING");break;
    case FALLING: Serial.println("Type: FALLING");break;
    case CHANGE:  Serial.println("Type: CHANGE");break;
    }

  // pin 2
  attachInterrupt(0,int0,type);
}

void loop() {
if(signal0)
  {
  drawDisplay();
  Serial.print(millis());
  Serial.print(" ");
  Serial.println(t0);
  signal0=false;  
  }
delay(100);
}

void int0() {
t0++;
signal0=true;
}



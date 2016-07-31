 /**
 * Arduino Interrupt Counter Nokia 5110
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Counts interrupts on Arduino Uno pin 2 and displays them on Nokia 5110.
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

// Nokia 5110 has 48 rows
int data[48];

volatile boolean signal0=false;
volatile int t0=0;
int32_t t0last=0;

// touch buttons
//const int type=RISING;

// buttons with pull-up resistor
const int type=FALLING;

//const int type=CHANGE;

void setup() {
Serial.begin(9600); 
Serial.println("Arduino Interrupt Counter");
switch(type)
  {
  case RISING:  Serial.println("Type: RISING");break;
  case FALLING: Serial.println("Type: FALLING");break;
  case CHANGE:  Serial.println("Type: CHANGE");break;
  }

// clear data
for(int i=0;i<48;i++)
  data[i]=0;

// init display
display.begin();
display.setContrast(60);
display.clearDisplay();
display.display();

// pin 2
attachInterrupt(0,int0,type);
}

void loop() {
int dif=t0-t0last;
Serial.print(millis());
Serial.print(" ");
Serial.println(dif);

// rotate data
for(int i=0;i<47;i++)
  data[i]=data[i+1];
// set last item
data[47]=constrain(dif,0,83);
t0last=t0;

// draw data
display.clearDisplay();
for(int i=0;i<48;i++) {
  display.drawLine(0,i,data[i],i,BLACK);
  }
display.fillRect(40,0,21,11,BLACK);
display.fillRect(41,1,19,9,WHITE);
display.setCursor(42,2);
display.print(dif);
display.display();

delay(1000);
}

void int0() {
t0++;
}


/**
 * Nokia 5110 Random Clock
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Creates PWM signal of frequency 2 MHz
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

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);


void setup() {
  // put your setup code here, to run once:
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  display.display(); // show splashscreen

  //Serial.begin(9600);
  //drawClock(1,15,32);
  //drawClock(1,15,0);
}

void loop() {
  int h=random(24);
  int m=random(60);
  int s=random(60);
  for(int i=0;i<10;i++)
    {
    drawClock(h,m,s);
    delay(1000);
    s++;
    if(s>=60) m++;
    s=s%60;
    if(m>=60) h++;
    m=m%60;
    h=h%24;
    }
}

void drawClock(int h, int m, int s)
{
const int r=23;
const double rot=-M_PI/2;
double x,y,x0,y0,anglerad;
  
  display.clearDisplay();
  display.drawPixel(24,24,BLACK);
  for(int i=0;i<12;i++)
    {
    int angled=360/12*i;
    anglerad=2*M_PI/12*i+rot;
    x=r*cos(anglerad);
    y=r*sin(anglerad);
    x0=(r-3)*cos(anglerad);
    y0=(r-3)*sin(anglerad);
    /*Serial.print(i);
    Serial.print(",");
    Serial.print(angled);
    Serial.print(",");
    Serial.print(anglerad);
    Serial.print(",");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println("");*/
    display.drawLine(24+x0,24+y0,24+x,24+y,BLACK);
    }

  // hour
  display.setCursor(50,0);
  display.print("h=");
  display.print(h);
  anglerad=2*M_PI/12*(h%12)+2*M_PI/12/60*m+rot;
  x=(r-15)*cos(anglerad);
  y=(r-15)*sin(anglerad);
  x0=0;
  y0=0;
  display.drawLine(24+x0,24+y0,24+x,24+y,BLACK);
  
  // minute
  display.setCursor(50,9);
  display.print("m=");
  display.print(m);
  for(int i=0;i<=m;i++)
    {
    anglerad=2*M_PI/60*i+rot;
    x=(r-10)*cos(anglerad);
    y=(r-10)*sin(anglerad);
    if(i==m)
      display.drawCircle(24+x,24+y,1,BLACK);
    else  
      display.drawPixel(24+x,24+y,BLACK);
    }

  // second
  display.setCursor(50,18);
  display.print("s=");
  display.print(s);
  for(int i=0;i<=s;i++)
    {
    anglerad=2*M_PI/60*i+rot;
    x=(r-5)*cos(anglerad);
    y=(r-5)*sin(anglerad);
    if(i==s)
      display.drawCircle(24+x,24+y,1,BLACK);
    else  
      display.drawPixel(24+x,24+y,BLACK);
    }

  // border
  display.drawLine(0,0,3,0,BLACK);
  display.drawLine(0,0,0,3,BLACK);
  display.drawLine(0,47,3,47,BLACK);
  display.drawLine(0,47,0,47-3,BLACK);
  display.drawLine(83,0,83-3,0,BLACK);
  display.drawLine(83,0,83,3,BLACK);
  display.drawLine(83,47,83-3,47,BLACK);
  display.drawLine(83,47,83,47-3,BLACK);
  
  display.display();  
}


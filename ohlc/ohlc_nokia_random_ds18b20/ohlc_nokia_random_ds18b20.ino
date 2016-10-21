/**
 * OHLC Nokia 5110 DS18B20 Candlestick Chart
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * 12 OHLC bars. 1 bar = 1 hour. Temperature measurements every 10 secs.
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
#include "candlestick.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// Speed
// define SPEED_HOURS in normal conditions
// undef it in fast demo
#define SPEED_HOURS

#ifdef SPEED_HOURS
  // 10 secs between measurements
  #define MEASURE_DELAY 10000L
#else
  #define MEASURE_DELAY 200
#endif

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// use your DS18B20 address
const DeviceAddress da[]={
  {0x28,0x49,0xBD,0x44,0x06,0x00,0x00,0x61}  // sensor 0
};

const int dacount=sizeof(da)/sizeof(DeviceAddress);

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#ifdef SPEED_HOURS
  // 12 bars, 60 min/bar, bar renderer
  OHLCChart<double, 12, 60000L*60, OHLCNokia5110BarRender<double> > ohlc;
#else
  // 12 bars, 10 sec/bar, bar renderer
  OHLCChart<double, 12, 10000L, OHLCNokia5110BarRender<double> > ohlc;
#endif  

double value=0.;

void setup() {
  Serial.begin(9600);

  // DS18B20
  sensors.begin();
  sensors.setResolution(da[0], TEMPERATURE_PRECISION);
  sensors.requestTemperatures();
  value = sensors.getTempC(da[0]);

  // connect renderer to Nokia 5110
  ohlc.getRender().setDisplay(&display);
  ohlc.setGridStep(1.);

  // Nokia 5110 init
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  display.display();
}

void loop() {
  sensors.requestTemperatures();
  value = sensors.getTempC(da[0]);
  //Serial.println(value);
  ohlc.addValue(value);

  // render chart
  display.clearDisplay();
  // draw candlesticks
  ohlc.draw();
  // draw last value
  display.fillRect(5,5,5+5*5+3,11,BLACK);
  display.fillRect(6,6,5+5*5+1,9,WHITE);
  display.setCursor(7,7);
  display.print(value);
  // draw indicator
  int _v=fmap(value,ohlc.minimum,ohlc.maximum,0.,47.);
  display.drawLine(82,47-_v,83,47-_v,BLACK);
  display.drawLine(83,47-_v+1,83,47-_v-1,BLACK);
  display.display();
  
  delay(MEASURE_DELAY); // 5 values/second
} 

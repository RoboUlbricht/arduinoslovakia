 /**
 * Arduino Uno - NeoPixel Clock
 * v. 1.0
 * Copyright (C) 2015 Robert Ulbricht
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

#include <Adafruit_NeoPixel.h>

// data pin
#define PIN 6
// led count
#define CNT 12
// shift of first led
#define MOVE 6
// show milliseconds
#define SHOWMILLIS 0
// show long hour
#define SHOWLONGHOUR 0
// show long minute
#define SHOWLONGMINUTE 0

// we do not have realtime
// use 24h time, for example 19:15
#define STARTHOUR 19
#define STARTMINUTE 15

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(CNT, PIN, NEO_GRB + NEO_KHZ800);

uint32_t milli_color   = strip.Color ( 10,  0,  0);
uint32_t milli_color1  = strip.Color (  6,  0,  0);
uint32_t milli_color2  = strip.Color (  3,  0,  0);

uint32_t second_color  = strip.Color (  0,  0, 3);
uint32_t second_color1 = strip.Color (  0,  0, 2);
uint32_t second_color2 = strip.Color (  0,  0, 1);

uint32_t hour_color    = strip.Color (  0, 3,  0);
uint32_t hour_color1   = strip.Color (  0, 2,  0);
uint32_t hour_color2   = strip.Color (  0, 1,  0);

uint32_t minute_color  = strip.Color (  3, 3, 3);
uint32_t minute_color1 = strip.Color (  2, 2, 2);
uint32_t minute_color2 = strip.Color (  1, 1, 1);

uint32_t off_color     = strip.Color (  0,  0,  0);

///
/// Main clock
///
class NeoClock
{
  uint8_t milli;
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  Adafruit_NeoPixel &strip;
 public:

  NeoClock(Adafruit_NeoPixel&);
  void Update();
  void Draw();
  void Clear();
  void AddColor(uint8_t position, uint32_t color);
  uint32_t Blend(uint32_t color1, uint32_t color2);
};

///
/// Constructor
///
NeoClock::NeoClock(Adafruit_NeoPixel& n_strip)
: strip (n_strip)
{
milli = second = minute = hour = 0;
}

///
/// Update all positions
///
void NeoClock::Update()
{
// we use fake time
uint32_t m=millis()+60000L*STARTMINUTE+3600000L*STARTHOUR;

second = map ((m % 60000), 0, 60000, 0, CNT);
milli  = map ((m %  1000), 0,  1000, 0, CNT);
minute = map (((m/60000) % 60), 0,  60, 0, CNT);
hour =   map (((m/60000/60) % 12), 0,  12, 0, CNT);
}

///
/// Set all colors
///
void NeoClock::Draw()
{
Clear();

#if SHOWLONGHOUR
AddColor((hour+MOVE)     % CNT,  hour_color  );
AddColor((hour+MOVE-1)   % CNT,  hour_color1  );
AddColor((hour+MOVE-2)   % CNT,  hour_color2  );
#else
AddColor((hour+MOVE)     % CNT,  hour_color  );
AddColor((hour+MOVE-1)   % CNT,  hour_color2  );
#endif

#if SHOWLONGMINUTE
AddColor((minute+MOVE)   % CNT,  minute_color);
AddColor((minute+MOVE-1) % CNT,  minute_color1);
AddColor((minute+MOVE-2) % CNT,  minute_color2);
#else
AddColor((minute+MOVE)   % CNT,  minute_color);
AddColor((minute+MOVE-1) % CNT,  minute_color2);
#endif
  
AddColor((second+MOVE)   % CNT, second_color);
AddColor((second+MOVE-1) % CNT, second_color1);
AddColor((second+MOVE-2) % CNT, second_color2);

#if SHOWMILLIS
AddColor((milli+MOVE)    % CNT,  milli_color);
AddColor((milli+MOVE-1)  % CNT,  milli_color1);
AddColor((milli+MOVE-2)  % CNT,  milli_color2);
#endif

strip.show();
}

///
/// Set color of LED
///
void NeoClock::AddColor(uint8_t position, uint32_t color)
{
uint32_t blended_color = Blend(strip.getPixelColor(position), color);

/* Gamma mapping */
uint8_t r,b,g;

r = (uint8_t)(blended_color >> 16),
g = (uint8_t)(blended_color >>  8),
b = (uint8_t)(blended_color >>  0);

strip.setPixelColor(position, blended_color);
}

///
/// Color blending
///
uint32_t NeoClock::Blend(uint32_t color1, uint32_t color2)
{
uint8_t r1,g1,b1;
uint8_t r2,g2,b2;
uint8_t r3,g3,b3;

r1 = (uint8_t)(color1 >> 16),
g1 = (uint8_t)(color1 >>  8),
b1 = (uint8_t)(color1 >>  0);

r2 = (uint8_t)(color2 >> 16),
g2 = (uint8_t)(color2 >>  8),
b2 = (uint8_t)(color2 >>  0);

return strip.Color(constrain(r1+r2, 0, 255), constrain(g1+g2, 0, 255), constrain(b1+b2, 0, 255));
}

///
/// Every LED to black
///
void NeoClock::Clear()
{
for(uint16_t i=0; i<strip.numPixels (); i++)
  strip.setPixelColor(i, off_color);
}

NeoClock clock(strip);

///
/// Setup
///
void setup()
{
strip.begin();
strip.show(); // Initialize all pixels to 'off'
}

///
/// Main loop
///
void loop()
{
clock.Update();
clock.Draw();
}

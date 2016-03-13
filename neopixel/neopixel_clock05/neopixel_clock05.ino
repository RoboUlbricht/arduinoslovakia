 /**
 * Arduino Uno - NeoPixel Clock
 * v. 1.4
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
#include "sma.h"
#include "clockdefs.h"
#include <button.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

// data pin
#define PIN 6
// button pin
#define SELECTPIN 2
#define PLUSPIN 5
#define MINUSPIN 4
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

// measure every 500 ms
#define STEPTIME 500
unsigned long lasttime=0;
// 64 items in buffer=32 s until full adaptation to light level
MovingAverage<uint16_t,64> ma;
// button, 25 ms debounce, no repeat, internal pull_up
Button b_select(SELECTPIN,ButtonActionSelect,25,0,true);
// button, 25 ms debounce, repeat 100 ms, internal pull_up
Button b_plus(PLUSPIN,ButtonActionPlus,25,100,true);
Button b_minus(MINUSPIN,ButtonActionMinus,25,100,true);

///
/// Program configuration
///
struct Configuration
{
ClockState cs;
bool show_millis;
int hour;
int minute;
int second;

Configuration()
: show_millis(SHOWMILLIS), cs(csClock), hour(STARTHOUR), minute(STARTMINUTE), second(0) {}
};
Configuration cfg;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(CNT, PIN, NEO_GRB + NEO_KHZ800);

uint32_t milli_color   = strip.Color ( 200,  0,  0);
uint32_t milli_color1  = strip.Color ( 160,  0,  0);
uint32_t milli_color2  = strip.Color (  60,  0,  0);

uint32_t second_color  = strip.Color (  0,  0, 200);
uint32_t second_color1 = strip.Color (  0,  0, 120);
uint32_t second_color2 = strip.Color (  0,  0,  60);

uint32_t hour_color    = strip.Color (  0, 200,  0);
uint32_t hour_color1   = strip.Color (  0, 160,  0);
uint32_t hour_color2   = strip.Color (  0,  60,  0);

uint32_t minute_color  = strip.Color (  200, 200, 200);
uint32_t minute_color1 = strip.Color (  160, 160, 160);
uint32_t minute_color2 = strip.Color (   60,  60,  60);

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
  
  void DrawClock();
  void DrawHour();
  void DrawMinute();
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
uint32_t m=millis()+1000L*cfg.second+60000L*cfg.minute+3600000L*cfg.hour;

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
  switch(cfg.cs)
    {
    case csClock:
      DrawClock();
      break;  
    case csHourSet:
      DrawHour();
      break;  
    case csMinuteSet:
      DrawMinute();
      break;  
    };
strip.show();
}

///
/// Draw the clock
///
void NeoClock::DrawClock()
{
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

if(cfg.show_millis)
  {
  AddColor((milli+MOVE)    % CNT,  milli_color);
  AddColor((milli+MOVE-1)  % CNT,  milli_color1);
  AddColor((milli+MOVE-2)  % CNT,  milli_color2);
  } 
}

///
/// Draw hours during setup
///
void NeoClock::DrawHour()
{
AddColor((hour+MOVE)     % CNT,  hour_color  );  
}

///
/// Draw minutes during setup
///
void NeoClock::DrawMinute()
{
// position/5
AddColor((minute+MOVE)   % CNT,  minute_color);
// tail as modulo 5
uint32_t m=millis()+60000L*cfg.minute+3600000L*cfg.hour;
int mm = (m/60000) % 60;
int mmm = mm % 5;
for(int i=0;i<mmm;i++)
  AddColor((minute+MOVE-i-1)   % CNT,  minute_color);
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
Serial.begin(9600);
while (!Serial) ; // wait for serial
Serial.println("NeoPixel Clock v. 1.4");
Serial.println("-------------------");
tmElements_t tm;
if (RTC.read(tm)) {
  Serial.print("Time = ");
  print2digits(tm.Hour);
  Serial.write(':');
  print2digits(tm.Minute);
  Serial.write(':');
  print2digits(tm.Second);
  Serial.print(", Date (D/M/Y) = ");
  Serial.print(tm.Day);
  Serial.write('/');
  Serial.print(tm.Month);
  Serial.write('/');
  Serial.print(tmYearToCalendar(tm.Year));
  Serial.println();
  
  cfg.second=tm.Second;
  cfg.minute=tm.Minute;
  cfg.hour=tm.Hour;
  }
  
strip.begin();
strip.show(); // Initialize all pixels to 'off'
strip.setBrightness(0); // disable flickering
}

///
/// Main loop
///
void loop()
{
// measure light every 500 ms
unsigned long ms=millis();
if(ms>lasttime)
  {
  uint16_t sv = analogRead(A0);
  ma.Push(sv);
  uint16_t sva = ma.MA();
  int svc=constrain(sva,300,900); // below 300 is always darkest brightness
  int m=map(svc,300,900,1,100); // we map this brightness to maximum value of brightness=100
  strip.setBrightness(m); // brightness 100 is enough on direct sun
  lasttime=ms+STEPTIME;
  }

// buttons
b_select.Read();
b_plus.Read();
b_minus.Read();

// clock
clock.Update();
clock.Draw();
}

///
/// When button is pressed
///
void ButtonActionSelect(Button *b)
{
if(b->pressed)
  {
  switch(cfg.cs)
    {
    case csClock:
      cfg.cs=csHourSet;
      break;  
    case csHourSet:
      cfg.cs=csMinuteSet;
      break;  
    case csMinuteSet:
      cfg.cs=csClock;
      break;  
    };
  }
}

void ButtonActionPlus(Button *b)
{
if(b->pressed)
  {
  switch(cfg.cs)
    {
    case csClock:
      cfg.show_millis=!cfg.show_millis; 
      break;  
    case csHourSet:
      cfg.hour++;
      if(cfg.hour>23)
        cfg.hour=0;
      break;  
    case csMinuteSet:
      cfg.minute++;
      if(cfg.minute>59)
        cfg.minute=0;
      break;  
    };
  }  
}

void ButtonActionMinus(Button *b)
{
if(b->pressed)
  {
  switch(cfg.cs)
    {
    case csClock:
      cfg.show_millis=!cfg.show_millis; 
      break;  
    case csHourSet:
      cfg.hour--;
      if(cfg.hour<0)
        cfg.hour=23;
      break;  
    case csMinuteSet:
      cfg.minute--;
      if(cfg.minute<0)
        cfg.minute=59;
      break;  
    };
  }  
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

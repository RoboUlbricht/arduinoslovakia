/**
 * Candlestick template library
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * 3 different renderers.
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

///
/// One OHLC bar data
///
template<typename ohlcvalue>
struct OHLCData {
  ohlcvalue o;
  ohlcvalue h;
  ohlcvalue l;
  ohlcvalue c;  
};

///
/// Serial port renderer
///
template<typename ohlcvalue>
class OHLCSerialRender {
public:
  void drawHeader() {
    Serial.println("###");
    }
  void drawBar(int pos, OHLCData<ohlcvalue> *value) {
    Serial.print(pos);
    Serial.print(",");
    Serial.print(value->o);
    Serial.print(",");
    Serial.print(value->h);
    Serial.print(",");
    Serial.print(value->l);
    Serial.print(",");
    Serial.print(value->c);
    Serial.println("");
    }
  void drawFooter() {}
};

///
/// Nokia 5110 Line Candlestick renderer
///
template<typename ohlcvalue>
class OHLCNokia5110LineRender {
  Adafruit_PCD8544 *display;
public:
  OHLCNokia5110LineRender() : display(NULL) {}
  void drawHeader() {
    }
  void drawBar(int pos, OHLCData<ohlcvalue> *bar) {
    if(display==NULL)
      return;
      
    int START = 5 + pos * 6;
    const int BW = 2;
    const int HEIGHT = 47;

    // open
    display->drawLine(START,HEIGHT-bar->o,START+1*BW,HEIGHT-bar->o,BLACK);

    // high - low
    display->drawLine(START+1*BW,HEIGHT-bar->h,START+1*BW,HEIGHT-bar->l,BLACK);

    // close
    display->drawLine(START+1*BW,HEIGHT-bar->c,START+2*BW,HEIGHT-bar->c,BLACK);
    }
  void drawFooter() {}
  void setDisplay(Adafruit_PCD8544 *d) {display=d;}
};

///
/// Nokia 5110 Bar Candlestick renderer
///

template<typename ohlcvalue>
class OHLCNokia5110BarRender {
  Adafruit_PCD8544 *display;
public:
  OHLCNokia5110BarRender() : display(NULL) {}
  void drawHeader() {
    }
  void drawBar(int pos, OHLCData<ohlcvalue> *bar) {
    if(display==NULL)
      return;
      
    int START = 5 + pos * 6;
    const int BW = 2;
    const int HEIGHT = 47;
    int top;
    int bottom;

    if(bar->o < bar->c) {
      top = bar->c;
      bottom = bar->o;
    } else {
      top = bar->o;
      bottom = bar->c;
    }

    // high
    display->drawLine(START+1*BW,HEIGHT-bar->h,START+1*BW,HEIGHT-top,BLACK);

    // low
    display->drawLine(START+1*BW,HEIGHT-bar->l,START+1*BW,HEIGHT-bottom,BLACK);

    // bar
    if(bar->o < bar->c) 
      display->drawRect(START,HEIGHT-bottom,2*BW+1,bottom-top+1,BLACK);
    else
      display->fillRect(START,HEIGHT-bottom,2*BW+1,bottom-top+1,BLACK);
    }
  void drawFooter() {}
  void setDisplay(Adafruit_PCD8544 *d) {display=d;}
};

///
/// OHLC recorder and renderer
/// ohlcvalue - int or float
/// len - number of bars
/// stp - time window (10000 = 10 seconds)
/// renderclass - which renderer we want to use
///
template<typename ohlcvalue, const int len, const int stp, typename renderclass>
class OHLCChart {
  OHLCData<ohlcvalue> data[len];
  const int ohlc_step;
  int ohlc_first;
  OHLCData<ohlcvalue> *last;
  unsigned long ohlc_next_step;
  renderclass render;
  
public:
  OHLCChart() : ohlc_step(stp), ohlc_first(len), ohlc_next_step(0) {
    last = data + (len - 1);
  }

  renderclass& getRender() {
    return render;
  }
  
  boolean addValue(ohlcvalue v) {
    unsigned long m=millis();
    if(m>ohlc_next_step) {
      if(ohlc_first>0)
        ohlc_first--;
      for(int i=0;i<(len-1);i++)
        data[i] = data[i+1];
      last->o = v;
      last->h = v;
      last->l = v;
      last->c = v;
      ohlc_next_step+=ohlc_step;
      return true;
    } else {
      if(last->h<v)
        last->h=v;
      if(last->l>v)
        last->l=v;
      last->c=v;
    }
  return false;
  }

  void draw() {
    render.drawHeader();
    for(int i=ohlc_first;i<len;i++)
      render.drawBar(i,data+i);
    render.drawFooter();
  }
};


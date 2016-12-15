/**
 * Candlestick template library
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * 5 different renderers. Grid. Autoscale.
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

#define TRACE(var)       \
 {                       \ 
 Serial.print("Trace: "); \
 Serial.print(#var);     \
 Serial.print("=");      \
 Serial.println(var);    \
 }

template<typename ohlcvalue>
ohlcvalue fmap(ohlcvalue x, ohlcvalue in_min, ohlcvalue in_max, ohlcvalue out_min, ohlcvalue out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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
/// OHLC recorder and renderer
/// ohlcvalue - int or float
/// len - number of bars
/// stp - time window (10000 = 10 seconds)
/// renderclass - which renderer we want to use
///
template<typename ohlcvalue, const int len, const long stp, typename renderclass>
class OHLCChart {
  OHLCData<ohlcvalue> data[len];
  const unsigned long ohlc_step;
  int ohlc_first;
  OHLCData<ohlcvalue> *last;
  unsigned long ohlc_next_step;
  renderclass render;
  ohlcvalue grid_step;
  
public:
  ohlcvalue minimum;
  ohlcvalue maximum;

  OHLCChart() : ohlc_step(stp), ohlc_first(len), ohlc_next_step(0) {
    last = data + (len - 1);
  }

  renderclass& getRender() {
    return render;
  }

  void setGridStep(ohlcvalue value) {
    grid_step = value;
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

  void addOhlc(OHLCData<ohlcvalue> d) {
    if(ohlc_first>0)
      ohlc_first--;
    for(int i=0;i<(len-1);i++)
      data[i] = data[i+1];
    *last = d;  
  }

  void draw() {
    render.drawHeader();
    if(ohlc_first!=len) {
      minimum = data[ohlc_first].l;
      maximum = data[ohlc_first].h;
      for(int i=ohlc_first+1;i<len;i++) {
        if(data[i].l<minimum)
          minimum = data[i].l;
        if(data[i].h>maximum)
          maximum = data[i].h;
      }
      if(grid_step>0 && minimum!=maximum)
        render.drawGrid(minimum,maximum,grid_step);
    }
    for(int i=ohlc_first;i<len;i++)
      render.drawBar(i,data+i,minimum,maximum);
    render.drawFooter();
  }

  void dump() {
    TRACE(len);
    TRACE(ohlc_first);
    for(int i=ohlc_first;i<len;i++)
      {
      TRACE(i);
      TRACE(data[i].o);
      TRACE(data[i].h);
      TRACE(data[i].l);
      TRACE(data[i].c);
      }
  }

};


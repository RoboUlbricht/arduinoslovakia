///
/// Nokia 5110 base renderer
///
template<class ohlcvalue>
class OHLCNokia5110BaseRender {
protected:
  Adafruit_PCD8544 *display;
public:
  OHLCNokia5110BaseRender() : display(NULL) {}

  void drawHeader() {}
  void drawFooter() {}
  void setDisplay(Adafruit_PCD8544 *d) {display=d;}
  void drawGrid(ohlcvalue minimum, ohlcvalue maximum, ohlcvalue grid_step) {
    const int HEIGHT = 47;
    int dv = minimum / grid_step;
    int _gs = fmap(minimum+grid_step,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    ohlcvalue bg = (dv + 0) * grid_step;
    for(ohlcvalue i = bg;i<maximum+grid_step;i+=grid_step) {
      for(int j=0;j<=84;j+=5)
        display->drawPixel(j,HEIGHT-(int)fmap(i,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT),BLACK);
      if(_gs>7) { // not too dense
        display->setCursor(0,HEIGHT-(int)fmap(i,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT)-7);
        display->print(i);
        }
      }
    }
};

///
/// Nokia 5110 Line Candlestick renderer
///
template<typename ohlcvalue>
class OHLCNokia5110LineRender : public OHLCNokia5110BaseRender<ohlcvalue> {
public:
  void drawBar(int pos, OHLCData<ohlcvalue> *bar, ohlcvalue minimum, ohlcvalue maximum) {
    if(this->display==NULL)
      return;
    if(minimum==maximum)
      return;

    OHLCData<ohlcvalue> _bar=*bar;
      
    int START = 5 + pos * 6;
    const int BW = 2;
    const int HEIGHT = 47;

    // transformation
    _bar.o = fmap(_bar.o,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.h = fmap(_bar.h,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.l = fmap(_bar.l,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.c = fmap(_bar.c,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);

    // open
    this->display->drawLine(START,HEIGHT-_bar.o,START+1*BW,HEIGHT-_bar.o,BLACK);

    // high - low
    this->display->drawLine(START+1*BW,HEIGHT-_bar.h,START+1*BW,HEIGHT-_bar.l,BLACK);

    // close
    this->display->drawLine(START+1*BW,HEIGHT-_bar.c,START+2*BW,HEIGHT-_bar.c,BLACK);
    }
};

///
/// Nokia 5110 Bar Candlestick renderer
///
template<class ohlcvalue>
class OHLCNokia5110BarRender : public OHLCNokia5110BaseRender<ohlcvalue> {
public:
  void drawBar(int pos, OHLCData<ohlcvalue> *bar, ohlcvalue minimum, ohlcvalue maximum) {
    if(this->display==NULL)
      return;
    if(minimum==maximum)
      return;

    OHLCData<ohlcvalue> _bar=*bar;
      
    int START = 5 + pos * 6;
    const int BW = 2;
    const int HEIGHT = 47;
    int top;
    int bottom;

    // transformation
    _bar.o = fmap(_bar.o,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.h = fmap(_bar.h,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.l = fmap(_bar.l,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.c = fmap(_bar.c,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);

    if(_bar.o < _bar.c) {
      top = _bar.c;
      bottom = _bar.o;
    } else {
      top = _bar.o;
      bottom = _bar.c;
    }

    // high
    this->display->drawLine(START+1*BW,HEIGHT-_bar.h,START+1*BW,HEIGHT-top,BLACK);

    // low
    this->display->drawLine(START+1*BW,HEIGHT-_bar.l,START+1*BW,HEIGHT-bottom,BLACK);

    // bar
    if(_bar.o < _bar.c) {
      this->display->fillRect(START,HEIGHT-bottom,2*BW+1,bottom-top+1,WHITE);
      this->display->drawRect(START,HEIGHT-bottom,2*BW+1,bottom-top+1,BLACK);
      }
    else
      this->display->fillRect(START,HEIGHT-bottom,2*BW+1,bottom-top+1,BLACK);
    }
};

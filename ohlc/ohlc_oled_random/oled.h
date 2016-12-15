///
/// OLED base renderer
///
template<class ohlcvalue>
class OHLCOledBaseRender {
protected:
  SSD1306 *display;
public:
  OHLCOledBaseRender() : display(NULL) {}

  void drawHeader() {}
  void drawFooter() {}
  void setDisplay(SSD1306 *d) {display=d;}
  void drawGrid(ohlcvalue minimum, ohlcvalue maximum, ohlcvalue grid_step) {
    const int HEIGHT = 63;
    int dv = minimum / grid_step;
    int _gs = fmap(minimum+grid_step,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    ohlcvalue bg = (dv + 0) * grid_step;
    for(ohlcvalue i = bg;i<maximum+grid_step;i+=grid_step) {
      for(int j=0;j<=128;j+=5)
        display->drawPixel(j,HEIGHT-(int)fmap(i,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT));
      if(_gs>7) { // not too dense
        display->setCursor(0,HEIGHT-(int)fmap(i,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT)-1);
        display->print(i);
        }
      }
    }
};

///
/// OLED Line Candlestick renderer
///
template<typename ohlcvalue>
class OHLCOledLineRender : public OHLCOledBaseRender<ohlcvalue> {
public:
  void drawBar(int pos, OHLCData<ohlcvalue> *bar, ohlcvalue minimum, ohlcvalue maximum) {
    if(this->display==NULL)
      return;
    if(minimum==maximum)
      return;

    OHLCData<ohlcvalue> _bar=*bar;
      
    int START = 5 + pos * 6;
    const int BW = 2;
    const int HEIGHT = 63;

    // transformation
    _bar.o = fmap(_bar.o,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.h = fmap(_bar.h,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.l = fmap(_bar.l,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.c = fmap(_bar.c,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);

    // open
    this->display->drawLine(START,HEIGHT-_bar.o,START+1*BW,HEIGHT-_bar.o);

    // high - low
    this->display->drawLine(START+1*BW,HEIGHT-_bar.h,START+1*BW,HEIGHT-_bar.l);

    // close
    this->display->drawLine(START+1*BW,HEIGHT-_bar.c,START+2*BW,HEIGHT-_bar.c);
    }
};

///
/// OLED Bar Candlestick renderer
///
template<class ohlcvalue>
class OHLCOledBarRender : public OHLCOledBaseRender<ohlcvalue> {
public:
  void drawBar(int pos, OHLCData<ohlcvalue> *bar, ohlcvalue minimum, ohlcvalue maximum) {
    if(this->display==NULL)
      return;
    if(minimum==maximum)
      return;

    //TRACE(minimum);
    //TRACE(maximum);

    OHLCData<ohlcvalue> _bar=*bar;
      
    int START = 5 + pos * 6;
    const int BW = 2;
    const int HEIGHT = 63;
    int top;
    int bottom;

    // transformation
    _bar.o = fmap(_bar.o,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.h = fmap(_bar.h,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.l = fmap(_bar.l,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);
    _bar.c = fmap(_bar.c,minimum,maximum,(ohlcvalue)0,(ohlcvalue)HEIGHT);

    //TRACE(pos);
    //TRACE(_bar.o);
    //TRACE(_bar.h);
    //TRACE(_bar.l);
    //TRACE(_bar.c);

    if(_bar.o < _bar.c) {
      top = _bar.c;
      bottom = _bar.o;
    } else {
      top = _bar.o;
      bottom = _bar.c;
    }

    //TRACE(top);
    //TRACE(bottom);

    // high
    this->display->drawLine(START+1*BW,HEIGHT-_bar.h,START+1*BW,HEIGHT-top);

    // low
    this->display->drawLine(START+1*BW,HEIGHT-_bar.l,START+1*BW,HEIGHT-bottom);

    // bar
    if(_bar.o < _bar.c) {
      this->display->setDrawColor(0);
      this->display->drawBox(START,HEIGHT-top,2*BW+1,top-bottom);
      this->display->setDrawColor(1);
      this->display->drawFrame(START,HEIGHT-top,2*BW+1,top-bottom);
      }
    else
      this->display->drawBox(START,HEIGHT-top,2*BW+1,top-bottom);
    }
};

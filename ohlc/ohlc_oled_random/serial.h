///
/// Serial port renderer
///
template<typename ohlcvalue>
class OHLCSerialRender {
public:
  void drawHeader() {
    Serial.println("###");
    }
  void drawGrid(ohlcvalue minimum, ohlcvalue maximum, ohlcvalue grid_step) {
    }
  void drawBar(int pos, OHLCData<ohlcvalue> *value, ohlcvalue minimum, ohlcvalue maximum) {
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


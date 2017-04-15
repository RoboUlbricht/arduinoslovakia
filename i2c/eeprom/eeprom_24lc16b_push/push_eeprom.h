class TemplatedEEPROM : public extEEPROM
{
  public:
    TemplatedEEPROM(eeprom_size_t deviceCapacity, byte nDevice, unsigned int pageSize, byte eepromAddr = 0x50)
      : extEEPROM(deviceCapacity, nDevice, pageSize, eepromAddr)
    {}

    template< typename T > T &get( int idx, T &t ) {
      uint8_t *ptr = (uint8_t*) &t;
      for ( int count = sizeof(T) ; count ; --count )
        *ptr++ = this->read(idx++);
      return t;
    }

    template< typename T > const T &put( int idx, const T &t ) {
      const uint8_t *ptr = (const uint8_t*) &t;
      for ( int count = sizeof(T) ; count ; --count )
        this->write(idx++, *ptr++);
      return t;
    }
};

template< typename data, const eeprom_size_t capacity>
class PushEEPROM : public TemplatedEEPROM
{
  const uint32_t _capacity = capacity*1024L;
  const uint32_t _maxbytes = _capacity/8;
  const uint32_t _maxitems = _maxbytes/sizeof(data);
  uint32_t       _index;
  
public:
  PushEEPROM(byte nDevice = 1, unsigned int pageSize = 16, byte eepromAddr = 0x50)
  : TemplatedEEPROM(capacity, nDevice, pageSize, eepromAddr),
  _index(0)
  {}

  const uint32_t getCapacity() { return _capacity; }
  const uint32_t getMaxBytes() { return _maxbytes; }
  const uint32_t getMaxItems() { return _maxitems; }

  bool push(data d) {
    if(_index>=_maxitems)
      return false;
    put(_index*sizeof(data),d);
    _index++;
    return true;
  }
  
};


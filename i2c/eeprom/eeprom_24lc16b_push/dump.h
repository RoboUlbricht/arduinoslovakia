template< typename T > void dumpHex(T &t) {
  int       theValue;
  char      textString[16];
  char      asciiDump[16];
  const uint8_t *myAddressPointer = (uint8_t*) &t;
  int mySize = sizeof(t);
  int maxrow;

  while (mySize > 0) {
    maxrow = min(16, mySize);
    sprintf(textString, "%04X - ", myAddressPointer);
    Serial.print(textString);
    for (int ii = 0; ii < maxrow; ii++) {
      theValue  = *myAddressPointer;
      sprintf(textString, "%02X ", theValue);
      Serial.print(textString);
      if ((theValue >= 0x20) && (theValue < 0x7f))
        asciiDump[ii]  = theValue;
      else
        asciiDump[ii]  = '.';
      myAddressPointer++;
    }
    asciiDump[maxrow] = 0;
    Serial.println(asciiDump);
    mySize -= maxrow;
  }
}

#define DUMP(var)        \
 {                       \ 
 Serial.print("Dump: "); \
 Serial.println(#var);   \
 dumpHex(var);           \
 }

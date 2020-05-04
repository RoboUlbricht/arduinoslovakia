#define RESERVED -1

class DumpRegister {
    int reg;
    const char *regname;
    int bits[8];
    const char *bitnames[8];

  public:
    DumpRegister(int _reg, const char *_regname,
                 int b7, int b6, int b5, int b4, int b3, int b2, int b1, int b0,
                 const char *bn7, const char *bn6, const char *bn5, const char *bn4,
                 const char *bn3, const char *bn2, const char *bn1, const char *bn0)
      : reg(_reg),
        regname(_regname)
    {
      bits[7] = b7; bitnames[7] = bn7;
      bits[6] = b6; bitnames[6] = bn6;
      bits[5] = b5; bitnames[5] = bn5;
      bits[4] = b4; bitnames[4] = bn4;
      bits[3] = b3; bitnames[3] = bn3;
      bits[2] = b2; bitnames[2] = bn2;
      bits[1] = b1; bitnames[1] = bn1;
      bits[0] = b0; bitnames[0] = bn0;
    }

    friend Print& operator << (Print &obj, DumpRegister &d);
};

Print& operator << (Print &obj, DumpRegister &d) {
  obj.print(d.regname);
  obj.print("=");
  int v = *(volatile uint8_t *)(d.reg);
  obj.print(v, BIN);
  obj.print(":");
  for (int i = 7; i >= 0; i--)
    if (d.bits[i] != -1 && v & (1 << i)) {
      obj.print(" ");
      obj.print(d.bitnames[i]);
    }
  obj.println("");
  return obj;
}

#define DREG(var, b7, b6, b5, b4, b3, b2, b1, b0) \
  DumpRegister dr_##var(&var, #var, b7, b6, b5, b4, b3, b2, b1, b0, #b7, #b6, #b5, #b4, #b3, #b2, #b1, #b0);

#define _(var) dr_##var

#define DUMPVAL(var)          \
  {                           \
    Serial.print(#var);       \
    Serial.print("=");        \
    Serial.println(var, BIN); \
  }

#ifndef __irtestdefine_h
#define __irtestdefine_h

// scancodes
#define vSTANDBY 0x807fc03f
#define vBTN1    0x807fe01f
#define vBTN2    0x807fa05f
#define vBTN3    0x807F609F
#define vBTN4    0x807FD02F
#define vBTN5    0x807F906F
#define vBTN6    0x807F50AF
#define vBTN7    0x807FF00F
#define vBTN8    0x807FB04F
#define vBTN9    0x807F708F
#define vBTN0    0x807F8877
#define vPLUS10  0x807F10EF
#define vMINUS10 0x807F08F7
#define vPLUS1   0x807F00FF
#define vMINUS1  0x807F38C7

///
/// Button enumeration
///
enum RButton
{
  rbStandby=0,
  rbBTN1,
  rbBTN2,
  rbBTN3,
  rbBTN4,
  rbBTN5,
  rbBTN6,
  rbBTN7,
  rbBTN8,
  rbBTN9,
  rbBTN0,
  rbPLUS10,
  rbMINUS10,
  rbPLUS1,
  rbMINUS1,
  rbUNKNOWN
};

#endif

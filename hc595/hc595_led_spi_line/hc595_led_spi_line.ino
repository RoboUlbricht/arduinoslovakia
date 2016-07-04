#include <SPI.h>

//Pin connected to ST_CP of 74HC595
// SS
int latchPin = 10;

//Pin connected to SH_CP of 74HC595
// SCK
int clockPin = 13;

// Pin connected to DS of 74HC595
// MOSI
int dataPin = 11;

char p1[]={
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b00001000,
  0b00000100,
  0b00000010,
};

char p2[]={
  0b00000001,
  0b00000011,
  0b00000110,
  0b00001100,
  0b00011000,
  0b00110000,
  0b01100000,
  0b11000000,
  0b10000000,
  0b11000000,
  0b01100000,
  0b00110000,
  0b00011000,
  0b00001100,
  0b00000110,
  0b00000011,
};

char p3[]={
  0b00000011,
  0b00000110,
  0b00001100,
  0b00011000,
  0b00110000,
  0b01100000,
  0b11000000,
  0b10000001,
};

char p4[]={
  0b00000000,
  0b00000001,
  0b00000011,
  0b00000111,
  0b00001111,
  0b00011111,
  0b00111111,
  0b01111111,
  0b11111111,
  0b01111111,
  0b00111111,
  0b00011111,
  0b00001111,
  0b00000111,
  0b00000011,
  0b00000001,
};

char pdivider[]={
  0b00000000,
  0b11111111,
};

void play(char *p,int poc, int repeat, int dela)
{
  while(repeat)
  {
    for (int i = 0; i < poc; i++) {
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:
      digitalWrite(latchPin, LOW);
      // shift out the bits:
      SPI.transfer(p[i]);

      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin, HIGH);
      // pause before next value:
      delay(dela);
    }
    repeat--;
  }
}

void divider()
{
play(pdivider,sizeof(pdivider),10,40);  
}

void setup() {
  //set pins to output so you can control the shift register
  SPI.begin ();
}

void loop() {
  play(p1,sizeof(p1),3,50*2);
  divider();
  play(p2,sizeof(p2),3,50*2);
  divider();
  play(p3,sizeof(p3),3,50*2);
  divider();
  play(p4,sizeof(p4),3,50*2);
  divider();
}




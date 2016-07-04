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

// Pin connected to OE of 74HC595
int pwmPin = 6;

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

void setup() {
  //set pins to output so you can control the shift register
  SPI.begin ();
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  int stp=20;
  for(int i=255;i>=0;i-=stp)
  {
    analogWrite(pwmPin,i);
    play(p4,sizeof(p4),1,50*2);
  }
  for(int i=0;i<256;i+=stp)
  {
    analogWrite(pwmPin,i);
    play(p4,sizeof(p4),1,50*2);
  }
}






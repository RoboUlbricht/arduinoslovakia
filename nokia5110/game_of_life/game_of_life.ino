/**
 * Nokia 5110 Game of Life
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Conway's Game of Life with more rules
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

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

uint8_t grid[42][3];
uint8_t ngrid[42][3];

struct rule
{
uint16_t s; // survive
uint16_t b; // born
char name[15];
};

const rule rules[]={
  {0b000001100,0b000001000,"S23/B3"},        // S23/B3 classic Game of Life
  {0b000111110,0b000001000,"S12345/B3"},     // S12345/B3 maze
  {0b000001100,0b001001000,"S23/B36"},       // S23/B36 HighLife
  {0b000000000,0b000000100,"/B2"},           // /B2 
  {0b000000000,0b000011100,"/B234"},         // /B234 
  {0b000000010,0b000000010,"S1/B1"},         // S1/B1 
  {0b100101010,0b010101000,"S1358/B357"},    // S1358/B357 
  {0b000111100,0b111110000,"S2345/B45678"},  // S2345/B45678 
  {0b111101100,0b111001000,"S235678/B3678"}, // S235678/B3678 
  {0b111101100,0b110001000,"S235678/B378"},  // S235678/B378 
};

const uint8_t nrules=sizeof(rules)/sizeof(rule);

#define gridRead(x,y) bitRead(grid[(x)][(y)/8],(y)%8)
#define gridSet(x,y) bitSet(grid[(x)][(y)/8],(y)%8)
#define gridClear(x,y) bitClear(grid[(x)][(y)/8],(y)%8)

uint8_t (*getNON)(uint8_t x, uint8_t y);

void setup() {
  Serial.begin(9600);

  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  drawIntro();
  display.display(); // show splashscreen

  randomSeed(analogRead(0));
}

void drawIntro()
{
display.setCursor(0,0);
display.print("Game of Life");
display.setCursor(0,20);
display.print("www.arduinoslovakia.eu");
display.display();
delay(2000);
display.clearDisplay();
display.setCursor(0,0);
display.print("Random rules examples. Each rule on fixed field or infinite field.");
display.display();
delay(2000);
}

void initGrid()
{
for(uint8_t i=0;i<42;i++)
  for(uint8_t j=0;j<24;j++)
    random(2) ? bitSet(grid[i][j/8],j%8) : bitClear(grid[i][j/8],j%8);
}

void drawGrid(uint8_t step)
{
for(uint8_t i=0;i<42;i++)
  for(uint8_t j=0;j<24;j++)
    {
    display.fillRect(i*2,j*2,2,2,gridRead(i,j) ? BLACK : WHITE);
    }

// border
display.drawLine(0,0,3,0,BLACK);
display.drawLine(0,0,0,3,BLACK);
display.drawLine(0,47,3,47,BLACK);
display.drawLine(0,47,0,47-3,BLACK);
display.drawLine(83,0,83-3,0,BLACK);
display.drawLine(83,0,83,3,BLACK);
display.drawLine(83,47,83-3,47,BLACK);
display.drawLine(83,47,83,47-3,BLACK);

// step
display.drawLine(0,47,step,47,BLACK);

display.display();
}

void nextStep(uint8_t rule)
{
for(uint8_t i=0;i<42;i++)
  for(uint8_t j=0;j<24;j++)
    {
    int near=getNON(i,j);
    if(canSurvive(rule,bitRead(grid[i][j/8],j%8),near))
      {
      bitSet(ngrid[i][j/8],j%8);
      }
    else
      {
      bitClear(ngrid[i][j/8],j%8);
      }
    }
for(uint8_t i=0;i<42;i++)
  for(uint8_t j=0;j<3;j++)
    grid[i][j]=ngrid[i][j];
}

uint8_t getNumberOfNeighbors(uint8_t x, uint8_t y)
{
if(x==0)
  {
  if(y==0)
    return                          (uint8_t)gridRead(x+1,y)+
           (uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
  else if(y==23)
    return (uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
                                   +(uint8_t)gridRead(x+1,y);
  else
    return (uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
                                   +(uint8_t)gridRead(x+1,y)+
           (uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
  }
if(x==41)
  {
  if(y==0)
    return (uint8_t)gridRead(x-1,y)                           +
           (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1);
  else if(y==23)
    return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+
           (uint8_t)gridRead(x-1,y);
  else
    return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+
           (uint8_t)gridRead(x-1,y)                           +
           (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1);
  }
if(y==0)
  return (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(x+1,y)+
         (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
if(y==23)
  return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
         (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(x+1,y);
return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
       (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(x+1,y)+
       (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
}

uint8_t getNumberOfNeighborsWithBorder(uint8_t x, uint8_t y)
{
if(x==0 || y==0 || x==41 || y==23)
  return 0;
return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
       (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(x+1,y)+
       (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
}

uint8_t getNumberOfNeighborsInfinite(uint8_t x, uint8_t y)
{
if(x==0)
  {
  if(y==0)
    return (uint8_t)gridRead(41,23)+(uint8_t)gridRead(x,23)+(uint8_t)gridRead(x+1,23)+
           (uint8_t)gridRead(41,y)                           +(uint8_t)gridRead(x+1,y)+
           (uint8_t)gridRead(41,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
  else if(y==23)
    return (uint8_t)gridRead(41,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
           (uint8_t)gridRead(41,y)                           +(uint8_t)gridRead(x+1,y)+
           (uint8_t)gridRead(41,0)+(uint8_t)gridRead(x,0)+(uint8_t)gridRead(x+1,0);
  else
    return (uint8_t)gridRead(41,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
           (uint8_t)gridRead(41,y)                           +(uint8_t)gridRead(x+1,y)+
           (uint8_t)gridRead(41,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
  }
if(x==41)
  {
  if(y==0)
    return (uint8_t)gridRead(x-1,23)+(uint8_t)gridRead(x,23)+(uint8_t)gridRead(0,23)+
           (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(0,y)+
           (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(0,y+1);
  else if(y==23)
    return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(0,y-1)+
           (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(0,y)+
           (uint8_t)gridRead(x-1,0)+(uint8_t)gridRead(x,0)+(uint8_t)gridRead(0,0);
  else
    return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(0,y-1)+
           (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(0,y)+
           (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(0,y+1);
  }
if(y==0)
  return (uint8_t)gridRead(x-1,23)+(uint8_t)gridRead(x,23)+(uint8_t)gridRead(x+1,23)+
         (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(x+1,y)+
         (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
if(y==23)
  return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
         (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(x+1,y)+
         (uint8_t)gridRead(x-1,0)+(uint8_t)gridRead(x,0)+(uint8_t)gridRead(x+1,0);
return (uint8_t)gridRead(x-1,y-1)+(uint8_t)gridRead(x,y-1)+(uint8_t)gridRead(x+1,y-1)+
       (uint8_t)gridRead(x-1,y)                           +(uint8_t)gridRead(x+1,y)+
       (uint8_t)gridRead(x-1,y+1)+(uint8_t)gridRead(x,y+1)+(uint8_t)gridRead(x+1,y+1);
}

uint8_t canSurvive(uint8_t r, uint8_t orig, uint16_t near)
{
if(orig)
  {
  return rules[r].s&(1<<near);
  }
else
  {
  return rules[r].b&(1<<near);
  }
}

void loopAlgo() {
for(uint8_t rule=0;rule<10;rule++)
  {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Rule: ");
  display.print(rule);
  display.setCursor(0,10);
  display.print(rules[rule].name);
  display.setCursor(0,20);
  display.print("getNON: ");
  display.print((int)getNON);
  display.display();
  delay(1000);
  
  initGrid();
  for(uint8_t step=0;step<84;step++)
    {
    nextStep(rule);
    drawGrid(step);
    delay(100);
    }
  }
}

void loop() {
getNON=getNumberOfNeighbors;
loopAlgo();
getNON=getNumberOfNeighborsWithBorder;
loopAlgo();
getNON=getNumberOfNeighborsInfinite;
loopAlgo();
}


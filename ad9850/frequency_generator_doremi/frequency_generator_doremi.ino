/**
 * Arduino Uno - AD9850 Frequency generator DoReMi
 * v. 1.0
 * Copyright (C) 2015 Robert Ulbricht
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

/*
The circuit:
 * LCD
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5 V and ground   
 * wiper to LCD VO pin (pin 3)
 *
 * AD9850
 * AD9850 GND to GND
 * AD9850 Vcc to +5 V
 * AD9850 W_CLK to digital pin 10
 * AD9850 FQ_UD to digital pin 9
 * AD9850 DATA to digital pin 8
 * AD9850 RESET to digital pin 7
 * AD9850 ZOUT1, ZOUT2, QOUT1, QOUT2 are outputs
 */

#include <ARDUINO_AD9850.h>
#include <LiquidCrystal.h>
#include "wiring_private.h"
#include "pitches.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
AD9850 device(10,9,8,7);

long frequency=0L; // initial frequency

int melody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};
int mdl=sizeof(melody)/sizeof(int);

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4,
  4, 4, 4, 4
};

///
/// Print frequency
///
void PrintFrequency()
{
char s[10];
ultoa(frequency,s,10);
int dl=strlen(s);
lcd.clear();
lcd.print("Freq=");
lcd.setCursor(16-dl, 0);
lcd.print(s);
}

///
/// Send Frequency
///
void SendFrequency()
{
device.osc(frequency,0);  
}

///
/// Setup
///
void setup()
{
// disable ADC
cbi(ADCSRA, ADEN);

device.init();
device.doReset();

// set up the LCD's number of columns and rows: 
lcd.begin(16, 2);
  
// Print a message to the LCD.
lcd.print("DoReMi");
lcd.setCursor(0, 1);
lcd.print("by RUR");
delay(200);
lcd.clear();

Serial.begin(9600);
Serial.println("AD9850 DoReMi");

SendFrequency();
PrintFrequency();

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < mdl; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    ad9850tone(melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    frequency=0;
    SendFrequency();
  }
}

///
/// Main loop
///
void loop()
{
}

///
/// Play and print frequency
///
void ad9850tone(long f, int dl)
{
frequency=f;  
SendFrequency();
PrintFrequency();
delay(dl);
}

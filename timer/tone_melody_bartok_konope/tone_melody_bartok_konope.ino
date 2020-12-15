/**
   Arduino Melody
   v. 1.0
   Copyright (C) 2020 Robert Ulbricht
   Copyright (C) 2011 Tom Igoe
   https://www.arduinoslovakia.eu

   16t. Konope, konope
   Béla Bartók - Slovenské ľudové piesne
   Zuzana Spišiaková, Poniky, 1916
   https://musescore.com/user/30544023/scores/6411435

   Plays a melody. 8 ohm speaker and 1k resistor on digital pin 8.

   IDE: 1.8.12 or higher
   Board: Arduino

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pitches.h"

// notes in the melody
int melody[] = {
  NOTE_G5, NOTE_F5, NOTE_E5, NOTE_G5,
  NOTE_C5, NOTE_G4,
  NOTE_G5, NOTE_F5, NOTE_E5, NOTE_G5,
  NOTE_C5, NOTE_G4,
  NOTE_G4, NOTE_C5,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_B4,
  NOTE_F4, NOTE_A4,
  NOTE_C5, NOTE_D5,
  NOTE_G4,
  NOTE_G4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8, 8, 8, 8,
  4, 4,
  8, 8, 8, 8,
  4, 4,
  4, 4,
  8, 8, 8, 8,
  4, 4,
  4, 4,
  2,
  4, 4
};

int notesLength = sizeof(melody)/sizeof(int);

// beats per minute
int bpm = 85;
// duration of a beat in ms
float beatDuration = 60.0 / bpm * 1000;

void setup() {
}

void loop() {
  for (int thisNote = 0; thisNote < notesLength; thisNote++) {

    float noteDuration = beatDuration * (4.0 / noteDurations[thisNote]);
    tone(8, melody[thisNote], noteDuration * 0.85);
    delay(noteDuration);
  }
  delay(500);
}

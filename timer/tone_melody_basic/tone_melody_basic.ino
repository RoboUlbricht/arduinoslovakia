/**
   Arduino Melody
   v. 1.0
   Copyright (C) 2020 Robert Ulbricht
   Copyright (C) 2011 Tom Igoe
   https://www.arduinoslovakia.eu

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
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
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

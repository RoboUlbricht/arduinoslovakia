/**
  Arduino MIDI - Korg Volca FM - Major Chords C, F, G and Amin
  v. 1.1
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.5 or higher

  Board: Arduino Uno or Arduino Pro Mini
  Core: https://github.com/arduino/ArduinoCore-avr
  Version: 1.6.21

  Libraries:
  MIDI library: https://github.com/FortySevenEffects/arduino_midi_library
  Version: 4.3.1

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

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();
const int channel = 1;
//                   C   C   C   C   F   F   F   F   A   A   A   A   G   G   G   G
const int notes[] = {60, 60, 60, 60, 65, 65, 65, 65, 69, 69, 69, 69, 67, 67, 67, 67};
const int inter[] = {0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0};
const int cnt = sizeof(notes) / sizeof(int);

const int interval_major[] = {0, 4, 7};
const int interval_minor[] = {0, 3, 7};
const int *intervals[] = {interval_major, interval_minor};

void setup() {
  MIDI.begin();
}

void loop() {
  int note;
  for (int i = 0; i < cnt; i++) {
    note = notes[i];
    for (int j = 0; j < 3; j++)
      MIDI.sendNoteOn(note + intervals[ inter[i] ][j], 64, channel);
    delay(160);
    for (int j = 0; j < 3; j++)
      MIDI.sendNoteOff(note + intervals[ inter[i] ][j], 64, channel);
    delay(40);
  }
}

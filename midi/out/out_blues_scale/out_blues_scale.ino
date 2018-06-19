/**
  Arduino MIDI - Korg Volca FM - Blues Scale
  v. 1.0
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
const int notes[] = {60, 63, 65, 66, 67, 70, 72};

void setup() {
  MIDI.begin();
}

void loop() {
  int note;
  for (int i = 0; i < sizeof(notes) / sizeof(int); i++) {
    note = notes[i];
    MIDI.sendNoteOn(note, 100, channel);
    delay(400);
    MIDI.sendNoteOff(note, 100, channel);
  }
  delay(2000);
}

/**
  Arduino Pro Micro - Ableton - MIDI
  v. 1.0
  Copyright (C) 2019 Robert Ulbricht
  https://www.arduinoslovakia.eu

  IDE: 1.8.6 or higher
  Board: Arduino Pro Micro
  Version: 1.6.22

  Libraries:
  MIDI Library
  https://github.com/FortySevenEffects/arduino_midi_library
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
#include <midi_UsbTransport.h>

static const unsigned sUsbTransportBufferSize = 16;
typedef midi::UsbTransport<sUsbTransportBufferSize> UsbTransport;

UsbTransport sUsbTransport;

MIDI_CREATE_INSTANCE(UsbTransport, sUsbTransport, MIDI);

const char *notenames[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

void printNoteName(int note)
{
  int octave = note / 12;
  int nnumber = note % 12;
  Serial.print(notenames[nnumber]);
  Serial.print(octave - 2);
}

void handleNoteOn(byte inChannel, byte inNumber, byte inVelocity)
{
  printNoteName(inNumber);
  Serial.print(" NoteOn  ");
  Serial.print(inNumber);
  Serial.print("\tvelocity: ");
  Serial.println(inVelocity);
}
void handleNoteOff(byte inChannel, byte inNumber, byte inVelocity)
{
  printNoteName(inNumber);
  Serial.print(" NoteOff ");
  Serial.print(inNumber);
  Serial.print("\tvelocity: ");
  Serial.println(inVelocity);
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  MIDI.begin();
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  Serial.println("Arduino MIDI note detector.");
}

void loop() {
  MIDI.read();
}

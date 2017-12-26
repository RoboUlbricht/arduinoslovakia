/**
 * Andrej Sládkovič and Arduino
 * v. 1.0
 * Copyright (C) 2017 Robert Ulbricht
 * https://www.arduinoslovakia.eu
 *
 * Board: Arduino MKR1000 or Arduino Zero
 * Core: Arduino SAMD 1.6.17
 * 
 * Last verse from Marina
 * Andrej Sladkovic: https://en.wikipedia.org/wiki/Andrej_Sl%C3%A1dkovi%C4%8D
 * Marina in Slovak: http://zlatyfond.sme.sk/dielo/17/Sladkovic_Marina/2
 * Translated: http://www.worldrecordacademy.com/arts/longest_love_poem_world_record_set_by_Marina_The-Poem-1_217099.html
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

#include "marina.h"

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  // last verse in Slovak
  Serial.print(marina[290]);
}

void loop() {
  // nothing
}

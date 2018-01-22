/**
   Finite State Machine - Blink
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Arduino sends data from temperature sensors DS18B20.
   Node.js receives data and converts them into the object.
   Use 2-3 sensors to see the parsed data.

   IDE: 1.8.5 or higher
   Board: Arduino or Arduino Pro Mini
   
   Libraries:
   arduino-fsm: 2.2.0
   https://github.com/jonblack/arduino-fsm

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

#include "Fsm.h"

// Used pins
#define LED_PIN LED_BUILTIN

// State machine variables
#define FLIP_LIGHT_SWITCH 1

State state_light_on(on_light_on_enter, NULL, &on_light_on_exit);
State state_light_off(on_light_off_enter, NULL, &on_light_off_exit);
Fsm fsm(&state_light_off);

// Transition callback functions
void on_light_on_enter() {
  Serial.println(__FUNCTION__);
  digitalWrite(LED_PIN, HIGH);
}

void on_light_on_exit() {
  Serial.println(__FUNCTION__);
  digitalWrite(LED_PIN, LOW);
}

void on_light_off_enter() {
  Serial.println(__FUNCTION__);
}

void on_light_off_exit() {
  Serial.println(__FUNCTION__);
}

void on_trans_light_on_light_off() {
  Serial.println(__FUNCTION__);
  Serial.println("  Transitioning from LIGHT_ON to LIGHT_OFF");
}

void on_trans_light_off_light_on() {
  Serial.println(__FUNCTION__);
  Serial.println("  Transitioning from LIGHT_OFF to LIGHT_ON");
}

// standard arduino functions
void setup() {
  Serial.begin(9600);
  Serial.println("FSM Light Switch");
  pinMode(LED_PIN, OUTPUT);

  fsm.add_transition(&state_light_on, &state_light_off,
                     FLIP_LIGHT_SWITCH,
                     &on_trans_light_on_light_off);
  fsm.add_transition(&state_light_off, &state_light_on,
                     FLIP_LIGHT_SWITCH,
                     &on_trans_light_off_light_on);
  fsm.run_machine();
}

void loop() {
  Serial.println("-- loop --");
  delay(2000);
  fsm.trigger(FLIP_LIGHT_SWITCH);
}

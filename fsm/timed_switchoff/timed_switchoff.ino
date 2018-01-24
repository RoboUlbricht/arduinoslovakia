/**
   Finite State Machine - Timed transitions
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   state 1:  led off
   state 2:  led on
   transition from s1 to s2 on button press
   transition back from s2 to s1 after 5 seconds or button press

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
#define LED_PIN     LED_BUILTIN
#define BUTTON_PIN  10

// Events
#define BUTTON_EVENT  0

// Button states and debounce
int buttonState = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

// States
State state_led_off(&led_off, &check_button, NULL);
State state_led_on(&led_on, &check_button, NULL);
Fsm fsm(&state_led_off);

void led_off() {
  Serial.println(__FUNCTION__);
  digitalWrite(LED_PIN, LOW);
}

void led_on() {
  Serial.println(__FUNCTION__);
  digitalWrite(LED_PIN, HIGH);
}

// Check button and debounce
void check_button() {
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState)
    lastDebounceTime = millis();

  if ((millis() - lastDebounceTime) > 50) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        Serial.println("button_pressed");
        fsm.trigger(BUTTON_EVENT);
      }
    }
  }

  lastButtonState = reading;
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  fsm.add_transition(&state_led_off, &state_led_on,
                     BUTTON_EVENT, NULL);
  fsm.add_timed_transition(&state_led_on, &state_led_off, 5000, NULL);
  fsm.add_transition(&state_led_on, &state_led_off, BUTTON_EVENT, NULL);
}

void loop() {
  fsm.run_machine();
}

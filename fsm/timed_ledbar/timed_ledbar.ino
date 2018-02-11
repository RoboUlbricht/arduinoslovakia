/**
   Finite State Machine - Timed transitions
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   state 1:  led off
   state 2:  led on
   state 3-10: LED bar
   transition from s1 to s2 on button press
   transition back from s2 to s1 after 5 seconds
   transition from sN to sN+1 on button press
   transition back from sN to s1 after N seconds

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

const int LED_BAR[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int LED_BAR_LENGTH = sizeof(LED_BAR) / sizeof(int);
int bar_position = 0;

// Events
#define BUTTON_EVENT  0

// Button states and debounce
int buttonState = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

// States
State state_led_off(&led_off, &check_button, NULL);
State state_led_on(&led_on,   &check_button, NULL);
State state_led1(&led_enter,  &check_button, NULL);
State state_led2(&led_enter,  &check_button, NULL);
State state_led3(&led_enter,  &check_button, NULL);
State state_led4(&led_enter,  &check_button, NULL);
State state_led5(&led_enter,  &check_button, NULL);
State state_led6(&led_enter,  &check_button, NULL);
State state_led7(&led_enter,  &check_button, NULL);
State state_led8(&led_enter,  &check_button, &led_leave);
Fsm fsm(&state_led_off);

void led_off() {
  Serial.println(__FUNCTION__);
  digitalWrite(LED_PIN, LOW);
  for (int i = 0; i < LED_BAR_LENGTH; i++)
    digitalWrite(LED_BAR[i], LOW);
  bar_position = 0;
}

void led_on() {
  Serial.println(__FUNCTION__);
  digitalWrite(LED_PIN, HIGH);
}

void led_enter() {
  Serial.println(__FUNCTION__);
  if (bar_position < LED_BAR_LENGTH)
    bar_position++;
  for (int i = 0; i < bar_position; i++)
    digitalWrite(LED_BAR[i], HIGH);
  for (int i = bar_position; i < LED_BAR_LENGTH; i++)
    digitalWrite(LED_BAR[i], LOW);
}

void led_leave() {
  Serial.println(__FUNCTION__);
  bar_position = 0;
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
  for (int i = 0; i < LED_BAR_LENGTH; i++)
    pinMode(LED_BAR[i], OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // on/off
  fsm.add_transition(      &state_led_off, &state_led_on, BUTTON_EVENT, NULL);
  fsm.add_timed_transition(&state_led_on,  &state_led_off, 5000, NULL);

  // LED bar button
  fsm.add_transition(      &state_led_on,  &state_led1, BUTTON_EVENT, NULL);
  fsm.add_transition(      &state_led1,    &state_led2, BUTTON_EVENT, NULL);
  fsm.add_transition(      &state_led2,    &state_led3, BUTTON_EVENT, NULL);
  fsm.add_transition(      &state_led3,    &state_led4, BUTTON_EVENT, NULL);
  fsm.add_transition(      &state_led4,    &state_led5, BUTTON_EVENT, NULL);
  fsm.add_transition(      &state_led5,    &state_led6, BUTTON_EVENT, NULL);
  fsm.add_transition(      &state_led6,    &state_led7, BUTTON_EVENT, NULL);
  fsm.add_transition(      &state_led7,    &state_led8, BUTTON_EVENT, NULL);
  fsm.add_transition(      &state_led8,    &state_led1, BUTTON_EVENT, NULL);
  // timed transitions
  fsm.add_timed_transition(&state_led1,    &state_led_off, 1000, NULL);
  fsm.add_timed_transition(&state_led2,    &state_led_off, 2000, NULL);
  fsm.add_timed_transition(&state_led3,    &state_led_off, 3000, NULL);
  fsm.add_timed_transition(&state_led4,    &state_led_off, 4000, NULL);
  fsm.add_timed_transition(&state_led5,    &state_led_off, 5000, NULL);
  fsm.add_timed_transition(&state_led6,    &state_led_off, 6000, NULL);
  fsm.add_timed_transition(&state_led7,    &state_led_off, 7000, NULL);
  fsm.add_timed_transition(&state_led8,    &state_led_off, 8000, NULL);
}

void loop() {
  fsm.run_machine();
}

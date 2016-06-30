/**
 * Data Change Stream Action
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * Example of action, when data stream changes value.
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

class DataChangeAction {
  int last_value;

public:
  DataChangeAction();

  bool NextValue(int value);
  void DoAction(int value);
};

DataChangeAction::DataChangeAction()
  : last_value(-1)
  {}

bool DataChangeAction::NextValue(int value) {
  if(value!=last_value) {
    DoAction(value);
    last_value=value;
    return true;
  }
  return false;
}

void DataChangeAction::DoAction(int value) {
  Serial.print("action=");
  Serial.println(value);
}

const int example_data[]={1,1,1,2,2,2,3,3,3,4,4,4,5,6,7,8,9};
const int example_size=sizeof(example_data)/sizeof(int);

void setup() {
  Serial.begin(9600);
  Serial.println("Data Change Stream Action");

  DataChangeAction dca;
  
  for(int i=0;i<example_size;i++) {
    int value=example_data[i];
    Serial.print("value=");
    Serial.println(value);
    dca.NextValue(value);
    }
}

void loop() {
}


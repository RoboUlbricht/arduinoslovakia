/**
   Serial communication between Arduino and Node.js
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Arduino sends. Node.js receives. Arduino simulates crash.
   Node.js closes connection and tries to reopen serial port.

   IDE: 1.8.5 or higher
   Board: Arduino Pro Mini
   
   Packages:
   serialport: ^6.0.5

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

'use strict';

const serialport = require('serialport');
const sp_readline = serialport.parsers.Readline;

class PortHandler {

  constructor(config) {
    this.config = config;
    this.last_data = Date.now();
    this.openPort();
  }

  openPort() {
    var self = this;
    this.port = new serialport(this.config.port, {
      baudRate: this.config.baudrate || 9600
      });

      const parser = new sp_readline();
      this.port.pipe(parser);
  
      this.port.on('close', function(error) {
        if(error)
          console.log('on close error', error.message);
        else
          console.log('on close');
      });
  
      parser.on('data', function(data) {
        self.last_data = Date.now();
        console.log(new Date(self.last_data).toLocaleTimeString(), data);
      });
  
      this.interval = setInterval(function() {
        console.log('Checking...');
        var millis = Date.now() - self.last_data;
        if(millis>10000) {
          console.log('Crash detected');
          self.port.close(function() {
            self.openPort();   
          });
          clearInterval(self.interval);
        }
      }, 5000);
  
  }
};

var idx = 0;
var ports = [];

serialport.list(function (err, p) {
  p.forEach(function(p) {
    ports.push(p.comName);
  });

  if(process.argv.length==2) {
    console.log('COM port list:');
    ports.forEach(function(p) {
      console.log(' [' + idx + '] ' + p);
      idx++;
    });
  }

  if(process.argv.length==3) {
    var port = ports[parseInt(process.argv[2])];
    console.log('Connecting to', port);
    const ph = new PortHandler({port: port, baudrate: 9600});
  }  
});


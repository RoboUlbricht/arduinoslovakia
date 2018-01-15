/**
   Serial communication between Arduino and Node.js
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Arduino sends data from temperature sensors DS18B20.
   Node.js receives data and converts them into the object.
   Use 2-3 sensors to see the parsed data.

   IDE: 1.8.5 or higher
   Board: Arduino Pro Mini
   
   Packages:
   serialport: ^6.0.0

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
const readline = require('readline');
const sp_readline = serialport.parsers.Readline;
const events = require('events');

class DS18B20Controller extends events.EventEmitter {

  constructor(config) {
    super();
    var self = this;
    this.config = config;
    this.port = new serialport(this.config.port, {
      baudRate: this.config.baudrate || 9600
      });
    const parser = new sp_readline();
    this.port.pipe(parser);

    parser.on('data', function(data){
      //console.log(data);
      var ar = data.trim().split(';');
      for(var i=0;i<ar.length;i+=2) {
        var t = {
          id: ar[i],
          temperature: parseFloat(ar[i+1])
        };
        self.emit('temperature', t);
      }
    });

    this.port.on('error', function(e) {
      console.error(e.message);
      process.exit(0);
    });

    this.port.on('open', function() {
      console.log('Serial Port Opened');
    });

    this.port.on('close', function(err) {
      console.log('Serial Port Closed: ' + err);
      process.exit(0);
    });

  }
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  prompt: 'select port> '
});

var idx = 0;
var ports = [];

console.log('COM port list:');
serialport.list(function (err, p) {
  p.forEach(function(p) {
    ports.push(p.comName);
    console.log(' [' + idx + '] ' + p.comName);
    idx++;
  });

  rl.prompt();
  
  rl.on('line', function(line) {
    //console.log(line);
    //console.log(ports);
    if(line<idx) {
      console.log('Opening ' + ports[Number(line)]);
      const ds18b20 = new DS18B20Controller({port: ports[Number(line)], baudrate: 9600});
      ds18b20.on('temperature', function(temp) {
        console.log('Temperature:', temp);
      });
  
    } else {
      console.error('ERROR: Wrong port number');
      process.exit(0);
    }
  });
  
  rl.on('close', function() {
    console.log('Bye!');
    process.exit(0);
  });

});



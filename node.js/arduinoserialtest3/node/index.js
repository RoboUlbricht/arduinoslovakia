/**
   Serial communication between multiple Arduinos and Node.js
   v. 1.1
   Copyright (C) 2017 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Multiple Arduinos sends. Node.js receives.

   IDE: 1.8.3 or higher
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

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  prompt: 'select ports (comma separated)> '
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
    var indexes = line.split(',')
      .map(function(item) {
        return item.trim();
      });
    //console.log(indexes);

    indexes.forEach(function(i) {
      if(i<idx) {
        console.log('Opening ' + ports[Number(i)]);

        const port = new serialport(ports[Number(i)], {
          baudRate: 9600
          });
        const parser = new sp_readline();
        parser.po=port.path;
        port.pipe(parser);  

        parser.on('data', function(data) {
          console.log(this.po + ':' + data);
        });
        
        port.on('error', function(e) {
          console.error(e.message);
          process.exit(0);
        });
        
        port.on('open', function() {
          console.log('Serial port ' + this.path + ' opened');
        });

        port.on('close', function(err) {
          console.log('Serial port closed: ' + err);
          process.exit(0);
        });

      } else {
        console.error('ERROR: Wrong port number');
        process.exit(0);
      }
    });
  });

  rl.on('close', function() {
    console.log('Bye!');
    process.exit(0);
  });

});

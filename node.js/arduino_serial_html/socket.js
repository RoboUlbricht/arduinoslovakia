/**
   Serial communication between Arduino and Node.js
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Arduino sends. Node.js receives.

   IDE: 1.8.4 or higher
   Board: Arduino Uno or Arduino Pro Mini
   
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

const serialport = require('serialport');
const sp_readline = serialport.parsers.Readline;

module.exports.connectSocket = function(server) {

  var io = require('socket.io')(server);
  var port;

  io.on('connection', function(socket){
    console.log('HTML page connected.');

    socket.on('disconnect', function(){
      console.log('HTML page disconnected.');
    });

    socket.on('do_connect', function(p) {
        if(port)
          return;
      console.log('do_connect:', p);
        port = new serialport(p, {
          baudRate: 9600
          });
        const parser = new sp_readline();
        port.pipe(parser);

      parser.on('data', function(data){
        data=data.replace('\r','');
        console.log('Arduino', data);
        io.emit('serial_data',data);
      });
        
      port.on('error', function(e) {
        console.error(e.message);
      });

      port.on('open', function() {
        console.log('Serial Port Opened');
      });

      port.on('close', function(err) {
        console.log('Serial Port Closed:', err);
      });
    });

    socket.on('do_disconnect', function(p) {
      if(port===undefined)
        return;
      console.log('do_disconnect:', p);
      port.close(function() {
        port=undefined;
      });
    });
  });

};

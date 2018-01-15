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

var serialport = require('serialport');

serialport.list(function (err, ports) {
  ports.forEach(function(port) {
    console.log(port.comName);
    console.log(' - pnpId: ' + port.pnpId);
    console.log(' - manufacturer: ' + port.manufacturer);
    console.log(' - serialNumber: ' + port.serialNumber);
    console.log(' - vendorId: ' + port.vendorId);
    console.log(' - productId: ' + port.productId);
  });
});
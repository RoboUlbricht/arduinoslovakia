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

var app = angular.module('arduinoSerialApp', []);

app.controller('arduinoSerialCtrl', ['$scope', '$http', function($scope, $http) {
  $scope.ports = [];
  $scope.lines = [];

  var socket = io();

  socket.on('serial_data', function(data) {
    $scope.data = data;
    $scope.lines.push(data);
    if($scope.lines.length>20)
      $scope.lines.shift();
    $scope.$apply();
  })

  $http.get('/port_list')
    .then(function(response) {
      console.log(response.data);
      $scope.ports = response.data;
      if($scope.ports.length)
        $scope.p = $scope.ports[0];
    }, function(error) {
      console.log(error);
    });

  $scope.doConnect = function() {
    socket.emit('do_connect', $scope.p.comName);
  };

  $scope.doDisconnect = function() {
    socket.emit('do_disconnect', $scope.p.comName);
    $scope.data = '';
    $scope.lines = [];
  };

}]);
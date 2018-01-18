/**
   Andrej Sládkovič - Marína
   v. 1.0
   Copyright (C) 2018 Robert Ulbricht
   https://www.arduinoslovakia.eu

   Node.js Marina app.

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

var app = angular.module('sladkovicApp', []);

app.controller('sladkovicCtrl', ['$scope', '$http', function($scope, $http) {

  $scope.verse = 1;
  $scope.maxverse = 1;
  $scope.text = '';

  $http.get('/marinaverses')
    .then(function(response) {
      console.log(response);
      $scope.maxverse = response.data.maxverse;
    }, function(error) {
      console.log(error);
    });

  updateText();

  function updateText() {
    $http.get('/marina?verse=' + $scope.verse)
      .then(function(response) {
        console.log(response);
        $scope.text = response.data;
      }, function(error) {
        console.log(error);
      });
  }

  $scope.doFirst = function() {
    if($scope.verse>1) {
      $scope.verse = 1;
      updateText();
    }
  }

  $scope.doPrev = function() {
    if($scope.verse>1) {
      $scope.verse--;
      updateText();
    }
  }

  $scope.doNext = function() {
    if($scope.verse<$scope.maxverse) {
      $scope.verse++;
      updateText();
    }
  }

  $scope.doLast = function() {
    if($scope.verse<$scope.maxverse) {
      $scope.verse = $scope.maxverse;
      updateText();
    }
  }

}]);
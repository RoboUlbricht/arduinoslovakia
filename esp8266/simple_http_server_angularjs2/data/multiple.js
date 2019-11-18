var app = angular.module('multipleApp', ['ngRoute']);

app.config(function ($routeProvider, $locationProvider) {
    $routeProvider.when('/', {
        controller: 'mainCtrl',
        templateUrl: '/page1.html',
    });

    $routeProvider.when('/history', {
        controller: 'historyCtrl',
        templateUrl: '/page2.html',
    });

    $routeProvider.otherwise({
        redirectTo: '/'
    });
});

app.controller('mainCtrl', ['$scope', '$http', function ($scope, $http) {

    function downloadData() {
        $http.get('data1.json')
        .then(function (response) {
            $scope.data = response.data;
        }, function (response) {
            $scope.error = response.data.error;
        });
    }

    downloadData();

}]);

app.controller('historyCtrl', ['$scope', '$http', function ($scope, $http) {

    function downloadData() {
        $http.get('data2.json')
        .then(function (response) {
            $scope.data = response.data;
        }, function (response) {
            $scope.error = response.data.error;
        });
    }

    downloadData();

}]);
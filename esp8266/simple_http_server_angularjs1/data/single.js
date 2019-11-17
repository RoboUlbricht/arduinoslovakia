var app = angular.module('singleApp', []);

app.controller('singleCtrl', ['$scope', '$http', function ($scope, $http) {

    function downloadData() {
        $http.get('data.json')
        .then(function (response) {
            $scope.data = response.data;
        }, function (response) {
            $scope.error = response.data.error;
        });
    }

    downloadData();

}]);
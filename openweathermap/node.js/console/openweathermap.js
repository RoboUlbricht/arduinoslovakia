/*
  Node.js - Weather forecast from https://openweathermap.org/
  v. 1.0
  Copyright (C) 2018 Robert Ulbricht
  https://www.arduinoslovakia.eu

  Permission to use, copy, modify, and/or distribute this software for any purpose with
  or without fee is hereby granted, provided that the above copyright notice and this
  permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
  TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
  NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
  DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
  IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
  IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

const request = require("request");

module.exports = class OpenWeatherMap {

	constructor(config) {
		this.config = config;
	}

	getCurrentWeatherByCityName(cityName, callback) {
		var self = this;
		request.get(`https://api.openweathermap.org/data/2.5/weather?q=${cityName}&units=${this.config.units}&APPID=${this.config.APPID}`,
			(err, data) => {
		    self.parseResponse(err, data, callback);
		})
	};

	getCurrentWeatherByCityID(cityId, callback) {
		var self = this;
		request.get(`https://api.openweathermap.org/data/2.5/weather?id=${cityId}&units=${this.config.units}&APPID=${this.config.APPID}`,
			(err, data) => {
		    self.parseResponse(err, data, callback);
		})
	};

	parseResponse(err, data, callback){
		var error = null;
		var response = null;
	
		error = err;
		if(data) {
			if(data.statusCode != 200) {
				var e = JSON.parse(data.body)
				error = new Error(e.message);
				error.status = e.cod;
			}
			if(data.body) {
				response = JSON.parse(data.body);
			}
		}
	
		callback(error, response);
	}

}  
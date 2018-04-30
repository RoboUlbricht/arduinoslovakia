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
		this.url = 'https://api.openweathermap.org/data/2.5/weather';
	}

	getCurrentWeatherByCityName(cityName) {
		return new Promise((resolve, reject) => {
			request.get(`${this.url}?q=${cityName}&units=${this.config.units}&APPID=${this.config.APPID}`,
				(err, data) => {
					this.parseResponse(err, data, resolve, reject);
			});
		});
	};

	getCurrentWeatherByCityID(cityId) {
		return new Promise((resolve, reject) => {
			request.get(`${this.url}?id=${cityId}&units=${this.config.units}&APPID=${this.config.APPID}`,
				(err, data) => {
					this.parseResponse(err, data, resolve, reject);
			});
		});
	};

	parseResponse(error, data, resolve, reject) {
		if(error)
			return reject(error);
		if(data.statusCode != 200) {
			let e = JSON.parse(data.body)
			let error = new Error(e.message);
			error.status = e.cod;
			return reject(error);
		}
		resolve(JSON.parse(data.body));
	}

}  
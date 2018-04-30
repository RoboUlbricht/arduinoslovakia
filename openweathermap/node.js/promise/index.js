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

const OpenWeatherMap = require('./openweathermap.js');

var cfg = {
		APPID: process.env.APPID || 'YOUR_APPID',
		units: "metric"
	};

var api = new OpenWeatherMap(cfg);

///
/// Current weather by city ID (Banska Bystrica)
///
/*api.getCurrentWeatherByCityID('3061186')
	.then((currentWeather) => {
		console.log(currentWeather);
	})
	.catch((error) => {
		console.log(error.message);
	});*/

///
/// Current weather by city name (Banska Bystrica)
///
api.getCurrentWeatherByCityName('Banska Bystrica')
	.then((currentWeather) => {
		console.log(currentWeather);
	})
	.catch((error) => {
		console.log(error.message);
	});

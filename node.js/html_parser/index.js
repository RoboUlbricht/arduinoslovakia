/**
 * Andrej Sládkovič from HTTP to C++
 * v. 1.0
 * Copyright (C) 2017 Robert Ulbricht
 * https://www.arduinoslovakia.eu
 *
 * Andrej Sladkovic: https://en.wikipedia.org/wiki/Andrej_Sl%C3%A1dkovi%C4%8D
 * Marina in Slovak: http://zlatyfond.sme.sk/dielo/17/Sladkovic_Marina/2
 * Translated: http://www.worldrecordacademy.com/arts/longest_love_poem_world_record_set_by_Marina_The-Poem-1_217099.html
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

var fs = require('fs');
const cheerio = require('cheerio');

var content = fs.readFileSync(__dirname + '/sladkovic-andrej_marina_txt.html');
const $ = cheerio.load(content);

var txt = $('.literallayout').text();
console.log(txt);
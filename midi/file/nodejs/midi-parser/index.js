let midiParser  = require('midi-parser-js');
let fs = require('fs');

let data = fs.readFileSync('./stupnica.mid');
let midiArray = midiParser.parse(data);

console.log(`Tracks: ${midiArray.tracks}, TimeDivision: ${midiArray.timeDivision}`);
for(let i in midiArray.track) {
  console.log(`Track ${i}`);
  for(let j in midiArray.track[i].event) {
    let event = midiArray.track[i].event[j];
    switch(event.type) {
      case 8: // note off
      case 9: // note on
      case 11: // controller
      case 12: // program change
        console.log(` ${j} t:${event.type} ch:${event.channel} delta:${event.deltaTime} - ${event.data}`);
        break;
      case 255: // meta event
        console.log(` ${j} t:${event.type} m:${event.metaType} delta:${event.deltaTime} - ${event.data}`);
        break;
      default:
        console.log(` ${j} t:${event.type} delta:${event.deltaTime} - ${event.data}`);
        break;
      }
  }
}

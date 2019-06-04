'use strict';

const fs = require('fs');

const readFile = (way) => 
  new Promise((resolve, reject) => 
    fs.readFile(way, 'utf8', (err, data) => err ? reject(err) : resolve(data))
  );

const wrap = (rF, way) => rF(way).then(console.log, console.error);
wrap(readFile, './json/info.json');

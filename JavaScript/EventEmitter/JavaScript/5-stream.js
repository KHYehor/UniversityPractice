'use strict';

const fs = require('fs');

const rs = fs.createReadStream('example.txt', 'utf8');

rs.on('open', () => {
  console.log('Stream is opened!');
});

rs.on('data', chunk => {
  console.log('----------------------chunk start----------------------');
  console.log(chunk);
  console.log('----------------------chunk end------------------------');
});

rs.on('close', () => {
  console.log('Stream is closed!');
});

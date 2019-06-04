'use strict';

const fs = require('fs');
const promisify = require('./promisify.js');
const readline = require('readline');
const array = ['./json/a.json', './json/b.json', './json/c.json', './json/d.json'];
const readFile = promisify(fs.readFile);

const rl = readline.createInterface({
  input: process.stdin, output: process.stdout
});

const arrayReadFile = arr => arr.forEach(el => readFile(el, 'utf8').then(console.log, console.error));

const RFarray = async arr => console.log(await Promise.all(arr.map(el => readFile(el, 'utf8'))));

arrayReadFile(array);
RFarray(array);

rl.question('Тут все не совсем синхронно...\n', (answer) => {
  console.log(`И твой ответ ниже прочитанных файлов-${answer}.`);
  rl.close();
});

'use strict';

const arr = [
  'a',
  1,
  true, 
  {value: 'key'},
  ['1', '2', '3'], 
  function a() {
    console.log(`simple function ${a}`);
  }
];

function SetExample(array) {
  this.set = array;
}

SetExample.prototype.iterator = function() {
  const arr = [];
  this.set.forEach(el => arr.push({ type: typeof el, value: el}));
  console.log(arr);
  return arr;
}

const array = new SetExample(arr);
array.iterator();

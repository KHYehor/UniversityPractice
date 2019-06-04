'use strict';

const object = {
  a: 'A',
  b: 2,
  c: false,
  sum3: (a, b, c) => {
    return a + b + c;
  },
  array: ['1', '2', '3', '4'],
  object: {a: 'a', b: 'b'}
}

function MapExample(obj) {
  this.map = obj;
}

MapExample.prototype.iterator = function() {
  const arr = [];
  Object.keys(this.map).forEach(el => arr.push({ key: el, type: typeof this.map[el], value: this.map[el] }));
  console.log(arr);
  return arr;
}

const obj = new MapExample(object);
obj.iterator();

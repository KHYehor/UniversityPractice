'use strict';

const obj1 = {
  a: 'a',
  b: 'b',
  text: 'this text exists only to check getter',
  sum3: {},
  simpleOperations: {},
  multiply: {},
  divide: {}
}

// implement mixin logable();

const mixin = (obj) => (
  obj['get'] = key => obj[key],
  obj['set'] = (key, value) => obj[key] = value
);

mixin(obj1);
console.log(obj1.get('text'));
obj1.set('c', 'd');
console.log(obj1);

'use strict';

const obj1 = { a: 'a', b: 'b', sum3: {}, simpleOperations: {}, multiply: {} };

// implement wrap(obj, ...funcs) 
// so if obj contains func.name 
// it should be wrapped

const divide = (a, b) => a / b;
const sum3 = (a, b, c) => a + b + c;
const simpleOperations = a => a * a / a + a - a; 

const wrap = (object, ...functions) => (
  functions.forEach(func => object[func.name] !== func ? object[func.name] = func : null),
  object
);

wrap(obj1, sum3, simpleOperations);
console.log(obj1);

'use strict';

const obj1 = { a: 'a', b: 'b', c: 'c' };
const obj2 = { a: 'a', d: 'd', g: 'g' };
const obj3 = { g: 'g', k: 'k', u: 'u', z: 'z' };
const obj4 = { s: 's', q: 'q', s: 's' };

// implement extend(obj, ...objects) 
// so keys from objects will be mixed 
// into obj only if it doesn't contain 
// those keys

const extend = (object, ...objects) => (
  objects.forEach(obj => 
    Object.keys(obj).forEach(key => 
      object[key] !== obj[key] ? object[key] = obj[key] : null 
    )
  ),
  object
);

extend(obj1, obj2, obj3, obj4);
console.log(obj1);

// This code makes absolutely
// the same.

// Object.assign(obj1, obj2, obj3, obj4);    
// console.log(obj1);                        

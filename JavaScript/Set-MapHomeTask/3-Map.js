'use strict';

const obj1 = {z: '0', x: '9'};
const array1 = ['a', 'b', 'c', 'd', 'e'];
const array2 = ['1', '2', '3', '4', '5', '6', '7'];

class map {
  constructor(object) {
    this.obj = object || {};
  }
  unite(arr1, arr2) {
    arr1.forEach((el, id) => this.obj[el] = arr2[id]);
    console.log(this.obj);
    return this.obj	
  }
}

const object = new map();
object.unite(array1, array2);
const object2 = new map(obj1);
object2.unite(array1, array2);

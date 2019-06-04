'use strict';

const Polygon = class {
  constructor(x, y, arr) {
    this.x = x; this.y = y; this.arr = arr;
  }

  toString() {
    return `${this.x}, ${this.y}, ${this.arr}`;
  }
};

// implement universal equilateral 
// mixin for for N sides


const equilateral = (Parent, N) => 
  class extends Parent {
    constructor(x, y, arr) {
      let sides = []; let i = 0;
      for(i; i < N; i++) sides.push(arr);
      super(x, y, sides);
      this.name = N + '-side equilateral';
    }
  }

const Pentagon = equilateral(Polygon, 5);
const p1 = new Pentagon(10, 20, 50);
console.log(p1.toString());
console.log(p1.name);
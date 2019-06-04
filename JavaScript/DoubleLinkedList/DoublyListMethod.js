'use strict';

function LinkedList() {
  this.first = null;
  this.last = null;
  this.length = 0;
  this[Symbol.iterator] = function() {
    let element = this.first;
    return {
      next() {
        this.current = element;
        if (this.current === null) return { value: null, done: true };
        element = element.next;
        return { value: this.current.data, done: false };
      }
    };
  };
}

function Node(list, data) {
  this.list = list;
  this.prev = null;
  this.data = data;
  this.next = null;
}

LinkedList.prototype.push = function(data) {
  const node = new Node(this, data);
  node.prev = this.last;
  if (!this.length) this.first = node;
  else this.last.next = node;
  this.last = node;
  this.length++;
  return this;
};

LinkedList.prototype.unshift = function(data) {
  const node = new Node(this, data);
  node.next = this.first;
  if (!this.length) this.first = node;
  else this.first.prev = node;
  this.first = node;
  this.length++;
  return this;
};

LinkedList.prototype.pop = function() {
  if (!this.length) return null;
  const node = this.last;
  this.last = node.prev;
  this.last.next = null;
  this.length--;
  return this;
};

LinkedList.prototype.shift = function() {
  if (!this.length) return null;
  const node = this.first;
  this.first = node.next;
  this.first.prev = null;
  this.length--;
  return this;
};

LinkedList.prototype.insert = function(index, element) {
  if (index > this.length + 1) {
    console.log(new Error('List length is less!').message);
    return;
  }
  let counter = 0;
  let current;
  // This algoritm looks difficult,
  // but it checks how to get the needed index is easier,
  // from tail to the id, or from the head to the id.
  // It was created to decrease the number of
  // list iterations - O(N) transforms to O(N/2).
  if (this.length - index < index) {
    this.unshift(element);
    let current = this.first;
    while (counter < index - 1) {
      current.data = current.next.data;
      current.next.data = current.data;
      current.next.prev.data = current.data;
      current = current.next;
      counter++;
    }
    current.data = element;
    return this;
  } else {
    this.push(element);
    current = this.last;
    while (counter < this.length - index - 1) {
      current.data = current.prev.data;
      current.prev.data = current.data;
      current.prev.next.data = current.data;
      current = current.prev;
      counter++;
    }
    current.data = element;
    return this;
  }
};

LinkedList.prototype.delete = function(index) {
  if (index > this.length) {
    console.log(new Error('List length is less!').message);
    return;
  }
  // This algoritm looks difficult,
  // but it checks how to get the needed index is easier,
  // from tail to the index, or from the head to the index.
  // It was created to decrease the number of
  // list iterations - O(N) transforms to O(N/2).
  let counter = 0;
  let current;
  if (this.length - index > index) {
    current = this.first;
    while (counter < index - 1) {
      current = current.next;
      counter++;
    }
    current.data = current.next.data;
    current.next = current.next.next;
    this.length--;
    return this;
  } else {
    current = this.last;
    while (counter < this.length - index - 1) {
      current = current.prev;
      counter++;
    }
    current.data = current.prev.data;
    current.prev = current.prev.prev;
    this.length--;
    return this;
  }
};

LinkedList.prototype.indexOf = function(element) {
  let current = this.first;
  let counter = 1;
  while (counter < this.length) {
    if (current.data.name === element) return counter;
    else {
      current = current.next;
      counter++;
    }
  }
  return false;
};

LinkedList.prototype.includes = function(element) {
  let current = this.first;
  let counter = 1;
  while (counter < this.length) {
    if (current.data.name === element) return true;
    else {
      current = current.next;
      counter++;
    }
  }
  return false;
};

LinkedList.prototype.map = function(callback) {
  let counter = 0;
  let current = this.first;
  while (counter < this.length) {
    current.data = callback(current.data);
    current = current.next;
    counter++;
  }
  return this;
};

const list = new LinkedList();

// I return from each prototype this,
// to make call like this.

list
  .push('first')
  .push('second')
  .push('third')
  .push('fivth')
  .push('sixth')
  .push('seventh')
  .insert(4, 'forth')
  .unshift('zero')
  .push('8th')
  .pop()
  .shift()
  .insert(8, 'eigth');

console.log('We cant add this element.');
list.insert(10, '10th');

console.log('It is also iterable and we can use it as array.');
console.log([...list]);

console.log('If I want to change every element, I can use map.');
list.map(el => ({ name: el }));
console.log([...list]);

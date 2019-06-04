'use strict';

function Memoize() {
  this.cache = {};
  this.argcall = [];
}

Memoize.prototype.syncfn = function(sfn) {
  this.sfn = sfn;
  return (...syncargs) => {
    this.argcall.push(syncargs);
    this.syncargs = syncargs;
    const key = this.syncargs;
    const val = this.cache[key];
    if (val) return val;
    const res = this.sfn(this.syncargs);
    this.cache[key] = res;
    return res;
  };
};

Memoize.prototype.getcache = function() {
  console.log(this.cache);
  return this.cache;
};

Memoize.prototype.clearcache = function() {
  this.cache = Object.create(null);
  console.log(`${this.cache} was cleared.`);
  return this;
};

Memoize.prototype.getcachesize = function() {
  console.log(Object.keys(this.cache).length);
  return Object.keys(this.cache).length;
};

Memoize.prototype.statistics = function() {
  const obj = {};
  const statistic = {};
  this.argcall.forEach(el => obj[el] = []);
  this.argcall.forEach(el => obj[el].push(el));
  Object.values(obj).forEach(el => statistic[`Arg ${el[0]}`] = `Called ${el.length} times.`);
  console.log(statistic);
  return this;
};

Memoize.prototype.addkey = function(key, value) {
  this.cache[key] = value;
  console.log(`Key ${key} was added - ${value}.`);
  return this;
};

Memoize.prototype.getkey = function(key) {
  if (this.cache[key] === 'undefined') console.log(`This key ${key} was not found.`);
  else console.log(this.cache[key]);
};

Memoize.prototype.delkey = function(key) {
  delete this.cache[key];
  console.log(`key ${key} was deleted.`);
};

Memoize.prototype.haskey = function(key) {
  if (Object.keys(this.cache).includes(key.toString())) {
    console.log('True');
    return true;
  } else {
    console.log('False');
    return false;
  }
};

module.exports = Memoize;

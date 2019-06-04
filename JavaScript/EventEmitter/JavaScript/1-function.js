'use strict';

const EventEmitter = function() {
  this.events = {};
};

EventEmitter.prototype.on = function(name, fn) {
  const event = this.events[name];
  if (event) event.push(fn);
  else this.events[name] = [fn];
};

EventEmitter.prototype.emit = function(name, ...data) {
  const event = this.events[name];
  if (event) event.forEach(fn => fn(...data));
};

const ee = new EventEmitter();

ee.on('meetup', data => {
  console.dir(`Толик узнал ${data}.`);
});

ee.on('meetup', data => {
  console.dir(`Даня обрадоволся что ${data}`);
});

ee.on('meetup', data => {
  console.dir(`Егор и так знал ${data}`);
});

ee.on('meetup', data => {
  console.dir(`Ваня выплатит кредит, потому что ${data}`);
});

ee.emit('meetup', 'мы получили деньги за проект!');

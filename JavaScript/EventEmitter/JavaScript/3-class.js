'use strict';


// это ООП стиль, но происходит ровно тоже самое что и в примере 2,
// как вам такая разница в написанном коде?
class OurEmitter {
  constructor(events = {}) {
    this.events = events;
  }
  on(name, cb) {
    const event = this.events[name];
    if (event) event.push(cb);
    else this.events[name] = [cb];
  }
  emit(name, ...args) {
    const event = this.events[name];
    if (event) event.forEach(fn => fn(...args));
  }
  once(name, cb) {
    const wrap = (...args) => {
      this.remove(name, wrap);
      cb(...args);
    };
    this.on(name, wrap);
  }
  names() {
    return Object.keys(this.events);
  }
  clear() {
    this.events = {};
  }
  listeners(name) {
    return (this.events[name] || []).slice();
  }
  remove(name, cb) {
    const event = this.events[name];
    if (!event) return;
    const i = event.indexOf(cb);
    if (i !== -1) event.splice(i, 1);
  }
  count(name) {
    return this.events[name].length;
  }
}

const ee = new OurEmitter();

ee.on('e1', data => {
  console.dir(data);
});

ee.emit('e1', { msg: 'e1 ok' });

ee.once('e2', data => {
  console.dir(data);
});

ee.emit('e2', { msg: 'e2 ok' });
ee.emit('e2', { msg: 'e2 not ok' });

const f3 = data => {
  console.dir(data);
};

ee.on('e3', f3);
ee.remove('e3', f3);
ee.emit('e3', { msg: 'e3 not ok' });

ee.on('e4', () => {});
ee.on('e4', () => {});
console.log('e4 count', ee.count('e4'));

ee.clear('e4');
ee.emit('e4', { msg: 'e4 not ok' });
ee.emit('e1', { msg: 'e1 ok' });

ee.clear();
ee.emit('e1', { msg: 'e1 not ok' });

ee.on('e5', () => {});
ee.on('e5', () => {});
ee.on('e6', () => {});
ee.on('e7', () => {});

console.log('listeners', ee.listeners('e5'));
console.log('names', ee.names());

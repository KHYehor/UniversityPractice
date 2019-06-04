'use strict';

// Это я расскажу и покажу вам так.

const EventEmitter = require('events');

const ee = new EventEmitter();

ee.once('event', data => {
  console.log(`Once: ${data}.`);
});

ee.emit('event', 'emit');

ee.on('event', data => {
  console.log(`On: ${data}`);
});

ee.emit('event', 'emit');

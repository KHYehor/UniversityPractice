'use strict';

/* Оригинал
const emitter = (l, o) => (l = {}, o = {
  on: (n, f) => (l[n] = l[n] || []).push(f),
  emit: (n, ...d) => (l[n] || []).map(f => f(...d)),
  once: (n, f, g) => o.on(n, g = (...a) => (f(...a), o.remove(n, g))),
  remove: (n, f, e) => (e = l[n] || [], e.splice(e.indexOf(f), 1)),
  clear: n => (n ? delete l[n] : l = {}),
  count: n => (l[n] || []).length,
  listeners: n => (l[n] || []).slice(),
  names: () => Object.keys(l)
});
*/

const emitter = (l, o) => (l = {}, o = {
// в строке выше мы получаем два якобы аргумента (l и o), но они сюда
// передаваться не будут, но вообще можно передать сюда готовый набор событий
// и набор методов обработчика событий, но не в этом примере;
// после идет второе функциональное выржение, его return, считайте это
// почти как ретурн функции но на самом деле ретурн набора команд

// и вот наш 'l' мы определяем как объект с событиями, где поле это
// название события а в значениях лежит массив функций(callback'ов)
// что обрабатывают данное событие

// а в 'о' лежит уже сам объект где в полях записаны имя функций а в
// в значении лежит сама функция и как бы когда мы делает
// const ee = emitter(); здесь возвращается (l = {}, o = {...});
// тоесть возвращается сам объект,( потому что по правилам из
// (arg1, arg2, arg3) вернется последний аргумент тоесть arg3 ),
// с функциями что работают с событиями что лежат в l
  on: (n, f) => (l[n] = l[n] || []).push(f),
  emit: (n, ...d) => (l[n] || []).map(f => f(...d)),
  once: (n, f, g) => o.on(n, g = (...a) => (f(...a), o.remove(n, g))),
  remove: (n, f, e) => (e = l[n] || [], e.splice(e.indexOf(f), 1)),
  clear: n => (n ? delete l[n] : l = {}),
  count: n => (l[n] || []).length,
  listeners: n => (l[n] || []).slice(),
  names: () => Object.keys(l)
  // сами функции расскажу вам на лекции или потом допишу сюда комментарии
});


// Если объясните этот код Тимуру, поясните каждую строчку, то
// у вас eсть шансы не уйти на переработку;

const ee = emitter();

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

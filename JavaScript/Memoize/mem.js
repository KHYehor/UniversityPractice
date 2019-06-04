'use strict';

const Memoize = require('./Memoize.js');
const factorial = n => n ? n * factorial(n - 1) : 1;

const mf = new Memoize();
const mfactorial = mf.syncfn(factorial);

mfactorial(15); 
mfactorial(13);
mfactorial(14);
mfactorial(12);
mfactorial(11);
mfactorial(16);
mfactorial(15);
mfactorial(15);

mf.statistics();
mf.getkey(15);
mf.getcache();
mf.getcachesize();
mf.addkey(2, 2);
mf.delkey(13);
mf.haskey(15);
mf.getcache();



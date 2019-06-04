'use strict';

module.exports = asyncFn => (...args) => 
	new Promise((resolve, reject) => (
		args.push((err, data) => err ? reject(err) : resolve(data)), 
		asyncFn.apply(this, args)
	));

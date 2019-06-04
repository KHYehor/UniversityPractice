'use strict';

const groups = ['IT-71', 'IT-72', 'IT-73', 'IT-74', 'IP-71', 'IP-72', 'IP-73'];

class SetExample {
  constructor(arr) {
    this.set = arr;
  }
  add(el) {
    this.set.push(el);
  }  
  delete(el) {
    if(this.set.includes(el)) delete this.set[this.set.indexOf(el)];
    else console.log(`Impossible to delete. ${el} does not exsist in this array.`);   
  }
  has(el) {
    if(this.set.includes(el)) console.log(`Array has ${el}.`);
    else console.log(`Array has not ${el}.`);
  }
  replace(el1, el2) {
    if(this.set.includes(el1)) {
      delete this.set[this.set.indexOf(el1)];
      this.set[this.set.indexOf(el1)] = el2;
    } else {
      console.log(`Array has not ${el1}.`);
    }
  }
}

const FICTgroups = new SetExample(groups);
FICTgroups.add('IP-74');
FICTgroups.delete('IP-74');
FICTgroups.delete('IK-72');
FICTgroups.has('IP-73');
FICTgroups.has('IP-74');
FICTgroups.replace('IT-71', 'IL-71');
console.log(FICTgroups);



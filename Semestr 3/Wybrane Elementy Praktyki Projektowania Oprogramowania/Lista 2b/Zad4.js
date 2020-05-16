// różnice:

const a = "I'm a string primitive";
const b = new String("I'm a String Object");

console.log(typeof a)   // 'string'
console.log(typeof b)   // 'object'

console.log(a instanceof String)    // false
console.log(b instanceof String)    // true





// tak należy sprawdzić, czy str jest stringiem:

function isString(str){
    return typeof str === 'string' || str instanceof String
}

console.log(isString(a))    // true
console.log(isString(b))    // true

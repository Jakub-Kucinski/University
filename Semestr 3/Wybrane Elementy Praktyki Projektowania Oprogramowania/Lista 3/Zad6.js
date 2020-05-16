function createGenerator(n) {
    var _state = 0;
    var _end = n;
    return {
        next: function () {
            return {
                value: _state,
                done: _state++ >= _end
            }
        }
    }
}

var foo = {
    [Symbol.iterator]: function () {return createGenerator(10) }
};

var foo2 = {
    [Symbol.iterator]: function () {return createGenerator(5) }
};

for (var f of foo)
    console.log(f);

for (var f of foo2)
console.log(f);
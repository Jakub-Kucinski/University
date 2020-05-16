var obiekt = {
    metoda: function () {
        return 100;
    },
    pole : 1,
    _wlasciwosc: 0,
    get bar() {
        return obiekt._wlasciwosc;
    },
    set bar(i) {
        obiekt._wlasciwosc = i;
    }
}

console.log(obiekt.bar);
obiekt.bar = 5;
console.log(obiekt.bar);
obiekt.fun = function (x) { return 2 * x };
console.log(obiekt.fun(5));

var obiekt2 = {
    _k : 13
}
//można
Object.defineProperty(obiekt2, 'qux', {
    get: function () {
        return obiekt2._k;
    }
});
//musi
Object.defineProperty(obiekt2, 'baz', {
    value: function () {
        return 34;
    }
});
//można
Object.defineProperty(obiekt2, 'pole', {
    value: 42
});

console.log(obiekt2.qux);
console.log(obiekt2.baz());
console.log(obiekt2.pole);

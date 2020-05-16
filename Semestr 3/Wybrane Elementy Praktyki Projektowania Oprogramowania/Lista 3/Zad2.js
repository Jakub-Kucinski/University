function sump(x) {
    var _sum = x;
    var _f = function (y) {
        _sum += y;
        return _f;
    }
    _f.valueOf = function () {
        return _sum;
    }
    return _f;
}

// console.log(sump(4)(5)(6) + 100);

function fac(n) {
    console.log('working for factorial(' + n + ')');
    if (n > 0) {
        return n * fac(n - 1);
    } else {
        return 1;
    }
}

function memoize(fn) {
    var cache = {};
    return function (n) {
        if (n in cache) {
            return cache[n]
        } else {
            var result = fn(n);
            cache[n] = result;
            return result;
        }
    }
}
// var memofac = memoize(fac);
// pierwsze wyliczenie –napełni cache
// console.log(memofac(6));
// drugie wyliczenie – z cache
// console.log(memofac(6));

function Fibrec(n)
{
    if (n == 1 || n == 2)
        return 1;
    return Fibrec(n - 1) + Fibrec(n - 2);
}

Fibrec = memoize(Fibrec);

function Fibiter(n)
{
    if (n == 1 || n == 2)
        return 1;
    var fiba;
    var fibb = 1;
    var fibc = 1;
    var i = 3;
    while (i <= n)
    {
        fiba = fibb;
        fibb = fibc;
        fibc = fiba + fibb;
        i += 1;
    }
    return fibc;
}

var Fibmemo = (function() {
    var memo = {};

    function f(n) {
        var value;
  
        if (n in memo) {
            return memo[n];
        } else {
            if (n === 0 || n === 1)
                value = n;
            else
                value = f(n - 1) + f(n - 2);
  
            memo[n] = value;
            return value;
        }
    }
    return f;
})();



for (var i = 10; i < 30; i = i + 1)
{
    console.log("n="+i.toString());
    console.time("Time rec");
    Fibrec(i);
    console.timeEnd("Time rec");
    console.time("Time iter");
    Fibiter(i);
    console.timeEnd("Time iter");
    console.time("Time memo");
    Fibmemo(i);
    console.timeEnd("Time memo");
}

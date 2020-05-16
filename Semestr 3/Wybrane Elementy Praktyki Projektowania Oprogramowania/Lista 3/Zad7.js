function fib() {
    var fib0 = 0;
    var fib1 = 1;
    var i = 0;
    return {
        next: function () {
            if (i >= 2) {
                let pom = fib0 + fib1;
                fib0 = fib1;
                fib1 = pom;
                i++;
                return {
                    value: pom,
                    done: false}
            }
            if (i == 0) {
                i++;
                return {
                    value: fib0,
                    done: false}
            }
            if (i == 1) {
                i++;
                return {
                    value: fib1,
                    done: false}
            }
        }
    }
}
function* fib2() {
    var fib0;
    yield 0;
    var fib1 = 0;
    yield 1;
    var fib2 = 1;
    while (true) {
        fib0 = fib1;
        fib1 = fib2;
        fib2 = fib0 + fib1;
        yield fib2;
    }
}

// var _it = fib();
// for (var _result; _result = _it.next(), !_result.done;) {
//     console.log(_result.value);
// }

// var _it = fib2();
// for (var _result; _result = _it.next(), !_result.done;) {
//     console.log(_result.value);
// }

// // Error
// for (var i of fib2()) {
//     console.log(i);
// }

// // Dziala
// for (var i of fib2()) {
//     console.log(i);
// }
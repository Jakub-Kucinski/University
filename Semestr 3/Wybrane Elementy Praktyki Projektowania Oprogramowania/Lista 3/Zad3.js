function forEach(a, f) {
    var l = a.length;
    var t = [];
    for (var i = 0; i < l; i++){
        t[i] = f(a[i])
    }
    // console.log(t);
    return t;
}

function map(a, f) {
    var l = a.length;
    var t = [];
    for (var i = 0; i < l; i++){
        t[i] = f(a[i]);
    }
    return t;
}

function filter(a, f) {
    var l = a.length;
    var t = [];
    for (var i = 0; i < l; i++){
        if (f(a[i])) {
            t.push(a[i]);
        }
    }
    return t;
}

var a = [1, 2, 3, 4];
forEach(a, _ => { console.log(_); });
// [1,2,3,4]
console.log(map(a, _ => _ * 2));
// [2,4,6,8]
console.log(filter(a, _ => _ < 3));
// [1,2]
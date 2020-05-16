function createFs(n) {
    // tworzy tablicę n funkcji
    var fs = [];
    // i-ta funkcja z tablicy ma zwrócić i
    for (var i = 0; i < n; i++) {
        fs[i] = function () {
            return i;
        };
    };
    return fs;
}
var myfs = createFs(10);
console.log(myfs[0]());
// zerowa funkcja miała zwrócić 0
console.log(myfs[2]());
// druga miała zwrócić 2
console.log(myfs[7]());
// 10 10 10

function createFs2(n) {
    // tworzy tablicę n funkcji
    var fs = [];
    // i-ta funkcja z tablicy ma zwrócić i
    for (let i = 0; i < n; i++) {
        fs[i] = function () {
            return i;
        };
    };
    return fs;
}
var myfs2 = createFs2(10);
console.log(myfs2[0]());
// zerowa funkcja miała zwrócić 0
console.log(myfs2[2]());
// druga miała zwrócić 2
console.log(myfs2[7]());
// 10 10 10

function createFs3(n) {
    // tworzy tablicę n funkcji
    var fs = [];
    // i-ta funkcja z tablicy ma zwrócić i
    for (var i = 0; i < n; i++) {
        fs[i] = (function (j) {
            //var j = i;
            return function () {
                return j;
            };
        })(i);
    };
    return fs;
}
var myfs3 = createFs3(10);
console.log(myfs3[0]());
// zerowa funkcja miała zwrócić 0
console.log(myfs3[2]());
// druga miała zwrócić 2
console.log(myfs3[7]());
// 10 10 10
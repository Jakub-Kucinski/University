function sum(...args) {
    var res = 0;
    args.forEach(e => {
        res += e;
    });
    return res;
}
console.log(sum());
console.log(sum(1, 2, 3));
console.log(sum(1, 2, 3, 4, 5));
(function (uwr) {
    uwr.Person = function (name) {
        this.name = name;
    }
})(global.UWr = global.UWr || {});

(function (uwr) {
    uwr.Worker = function (name) {
        this.name = name;
    }
})(global.UWr = global.UWr || {}); 

var p = new UWr.Person('jan');
var w = new UWr.Worker('Tomasz');
console.log(p.name);
console.log(w.name);
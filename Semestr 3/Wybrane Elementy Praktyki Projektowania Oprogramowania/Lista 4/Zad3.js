var Foo = function (name) {
    this.name = name;
    var Qux = function () {
        return "Prywatna";
    }
    this.Bar = function () {
        return Qux();
    }
}

var p = new Foo("nazwa");
console.log(p.Bar());
//Error
// console.log(p.Qux());
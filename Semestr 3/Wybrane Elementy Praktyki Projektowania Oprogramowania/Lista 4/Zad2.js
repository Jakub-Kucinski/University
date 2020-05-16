class Tree {
    constructor(value, left, right) {
        this.value = value;
        this.left = left;
        this.right = right;
    }
}

Tree.prototype.getIterator = function* () {
    yield this.value;
    if (this.left !== null) {
        yield* this.left.getIterator();
    }
    if (this.right !== null) {
        yield* this.right.getIterator();
    } 
}


var depth_3 = new Tree(1, new Tree(2, new Tree(4, null, null), new Tree(5, null, null)), new Tree(3, null, null));

var v = depth_3.getIterator()
for (var e of v) {
    console.log(e);
}
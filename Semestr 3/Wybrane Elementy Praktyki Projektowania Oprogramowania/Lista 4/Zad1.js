class Tree {
    constructor(value, left, right) {
        this.value = value;
        this.left = left;
        this.right = right;
    }
}

var depth_3 = new Tree(1, new Tree(2, new Tree(4, null, null), new Tree(5, null, null)), new Tree(3, null, null));

console.log(depth_3);
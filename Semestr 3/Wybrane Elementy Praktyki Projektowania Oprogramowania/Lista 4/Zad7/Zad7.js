const { once } = require('events');
// const once = require('events').once;
const { createReadStream } = require('fs');
const { createInterface } = require('readline');

(async function processLineByLine() {
    try {
        const rl = createInterface({
            input: createReadStream('logs.txt'),
            crlfDelay: Infinity
        });

        var t = {}
        
        rl.on('line', (line) => {
            var l = line.slice(9, 20);
            if (l in t) {
                t[l] += 1;
            } else {
                t[l] = 1;
            }
        });

        await once(rl, 'close');

        var p1, p2, p3;
        var v1 = 0;
        var v2 = 0;
        var v3 = 0;
        for (var prop in t) {
            val = t[prop];
            if (val > v3) {
                if (val > v2) {
                    if (val > v1) {
                        p3 = p2;
                        v3 = v2;
                        p2 = p1;
                        v2 = v1;
                        p1 = prop;
                        v1 = val;
                    } else {
                        p3 = p2;
                        v3 = v2;
                        p2 = prop;
                        v2 = val;
                    }
                } else {
                    p3 = prop;
                    v3 = val;
                }
            }
        }
        console.log(p1, " ", v1);
        console.log(p2, " ", v2);
        console.log(p3, " ", v3);
    }   catch (err) {
        console.error(err);
    }
})();
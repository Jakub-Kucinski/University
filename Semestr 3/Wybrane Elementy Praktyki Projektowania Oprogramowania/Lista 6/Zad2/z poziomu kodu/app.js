var http = require('http');
var express = require('express');
var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.get('/', (req, res) => {
    var combo1 = {
        name: 'combo1',
        options: [
            { value: 1, text: 'Ola' },
            { value: 2, text: 'Basia' },
            { value: 3, text: 'Jula' }
        ]
    };
    var combo2 = {
        name: 'combo2',
        options: [
            { value: 4, text: 'Ford Fiesta' },
            { value: 5, text: 'Toyota Avensis' },
            { value: 6, text: 'BMW X5' }
        ]
    }
    res.render('index', { combo1, combo2 });
});
http.createServer(app).listen(3000); 
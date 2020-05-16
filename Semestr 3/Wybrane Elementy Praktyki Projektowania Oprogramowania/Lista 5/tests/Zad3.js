var http = require('http');
var express = require('express');
var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');

app.use((req, res) => {
    res.setHeader('Content-disposition', 'attachment; filename="foo.txt"');
    var przelewy = [
        {kwota: 123, data: '2016-01-03', id: 1},
        { kwota: 124, data: '2016-01-02', id: 2 },
        { kwota: 125, data: '2016-01-01', id: 3 },
    ];
    
    res.end(res.render('index', {
        przelewy: przelewy
    }));
});

http.createServer(app).listen(3000);

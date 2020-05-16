var http = require('http');
var express = require('express');
var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.use(express.urlencoded({ extended: true })); 

app.get('/', (req, res) => {
    res.render('index5');
});

app.post('/print', (req, res) => {
    var imie = req.body.imie;
    var nazwisko = req.body.nazwisko;
    var nazwazajec = req.body.nazwazajec;
    var zadanie1 = req.body.zadanie1 || 0;
    var zadanie2 = req.body.zadanie2 || 0;
    var zadanie3 = req.body.zadanie3 || 0;
    var zadanie4 = req.body.zadanie4 || 0;
    var zadanie5 = req.body.zadanie5 || 0;
    var zadanie6 = req.body.zadanie6 || 0;
    var zadanie7 = req.body.zadanie7 || 0;
    var zadanie8 = req.body.zadanie8 || 0;
    var zadanie9 = req.body.zadanie9 || 0;
    var zadanie10 = req.body.zadanie10 || 0;
    res.render('index6', {
        imie: imie,
        nazwisko: nazwisko,
        nazwazajec: nazwazajec,
        zadanie1: zadanie1,
        zadanie2: zadanie2,
        zadanie3: zadanie3,
        zadanie4: zadanie4,
        zadanie5: zadanie5,
        zadanie6: zadanie6,
        zadanie7: zadanie7,
        zadanie8: zadanie8,
        zadanie9: zadanie9,
        zadanie10: zadanie10
    });
});

http.createServer(app).listen(3000); 
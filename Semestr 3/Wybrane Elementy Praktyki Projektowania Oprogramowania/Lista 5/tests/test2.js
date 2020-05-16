// var http = require('http');
// var express = require('express');
// var app = express();
// app.set('view engine', 'ejs');
// app.set('views', './views');
// app.use((req, res) => {
//     res.render('index');
// });
// http.createServer(app).listen(3000); 

var http = require('http');
var express = require('express');
var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.use((req, res) => {
    res.render('index5', {username:'foo'}); 
});
http.createServer(app).listen(3000); 
var http = require('http');
var express = require('express');
var cookieParser = require('cookie-parser');
var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.disable('etag');
app.use(cookieParser());
app.use(express.urlencoded({
    extended: true
}));
app.use("/", (req, res) => {
    var cookieValue;
    var cookieValue2;
    if (!req.cookies.cookie) {
        cookieValue = new Date().toString();
        res.cookie('cookie', cookieValue, { maxAge: 10000 });
        cookieValue2 = 'asdsadasasdsadfasdfsa';
        res.cookie('cookie2', cookieValue2, { maxAge: -1 });
    } else {
        cookieValue = req.cookies.cookie;
        cookieValue2 = req.cookies.cookie2;
    }
    res.render("index", { cookieValue: cookieValue, cookieValue2: cookieValue2 });
});
http.createServer(app).listen(3000);
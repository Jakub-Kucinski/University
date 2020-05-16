var http = require('http');
var express = require('express');
var session = require('express-session');
var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.disable('etag');

app.use(session({
    resave: true,
    saveUninitialized: true,
    secret: 'qewhiugriasgy'
}));

app.use("/", (req, res) => {
    var sessionValue;
    if (!req.session.sessionValue) {
        sessionValue = new Date().toString();
        req.session.sessionValue = sessionValue;
    } else {
        //sessionValue = req.session.sessionValue;
        //jest sesja - nie ma sesji
        req.session.destroy(function (err) {
            // cannot access session here
        })
    }
    res.render("index", { sessionValue: sessionValue });
});
http.createServer(app).listen(3000);
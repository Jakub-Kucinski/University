var http = require('http');
var express = require('express');
var multer = require('multer')
var upload = multer({ dest: 'uploads/' })

var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.post('/', upload.single('avatar'), function (req, res, next) {
    // req.file is the `avatar` file
    // req.body will hold the text fields, if there were any
    console.log("cokolwiek");
    try {
        res.send(req.file);
    } catch (err) {
        res.send(400);
    }
    console.log(new Date().toString());

})

app.use((req, res) => {
    console.log("hoho");
    res.render('index');
});

http.createServer(app).listen(3000);
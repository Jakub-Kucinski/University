var http = require('http');
var express = require('express');
var app = express();
var db = require('./database_handler');
app.use(express.static(__dirname + '/public'));
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: false }));
var id = null;

app.use('/login', (req, res, next) => {
    id = null;
    res.render('log_form.ejs')
});
app.post('/login_post', async (req, res, next) => {
    id = await db.log_in_user(req.body.name, req.body.paswd);
    if (id === null) {
        res.redirect('/login');
    } else {
        res.redirect('/');
    }
});
app.use('/login_admin', (req, res, next) => {
    res.render('admin_log_form.ejs')
});
app.post('/login_admin_post', async (req, res, next) => {
    id = await db.log_in_admin(req.body.name, req.body.paswd);
    if (id === null) {
        res.redirect('/login_admin');
    } else {
        res.redirect('/admin');
    }
});
app.use('/reg', (req, res, next) => {
    res.render('reg_form.ejs')
});
app.use('/edit', (req, res, next) => {
    res.render('product_form.ejs')
});
app.use('/add', (req, res, next) => {
    res.render('product_form.ejs')
});
app.use('/orders', (req, res, next) => {
    res.render('orders_look.ejs', {
        orders: [
            {
                usrname: 'Julia', value: "4", date: '20.01.2020', id: '1',
                products: [
                    { name: 'marchewka' },
                    { name: 'pietruszka' }
                ]
            },
            {
                usrname: 'Romeo', value: "3", date: '16.01.2020', id: '2',
                products: [
                    { name: 'marchewka' },
                    { name: 'banan' }
                ]
            }
        ],
        user: 'Gosia'
    });
});
app.use('/baskets', (req, res, next) => {
    res.render('baskets_look.ejs', {
        orders: [
            {
                usrname: 'Julia', value: "4", id: '1',
                products: [
                    { name: 'marchewka', date: '20.01.2020' },
                    { name: 'pietruszka', date: '20.01.2020' }
                ]
            },
            {
                usrname: 'Romeo', value: "3", id: '2',
                products: [
                    { name: 'marchewka', date: '20.01.2020' },
                    { name: 'banan', date: '20.01.2020' }
                ]
            }
        ],
        user: 'Gosia'
    });
});
app.use('/users', (req, res, next) => {
    res.render('users_look.ejs', {
        users: [
            { usrname: 'juleczka', name: "Julia", surname: "Szekspirowa", email: 'julciaromeowa@gmail.com' },
            { usrname: 'romuś', name: "Romeo", surname: "Szekspir", email: 'romus123@gmail.com' }
        ],
        admin: 'Gosia'
    });
});
app.use('/basket', (req, res, next) => {
    res.render('basket_look.ejs', {
        items: [
            { name: 'banan', img: '/images/Donald-duck.png', price: "4", date: '20.01.2020' },
            { name: 'marchewka', img: '/images/Donald-duck.png', price: "3", date: '16.01.2020' }
        ],
        user: 'Gosia'
    });
});
app.use('/log', (req, res, next) => {
    res.render('log_view.ejs', {
        products: [
            { name: 'banan', desc: 'zółty słodki owoc pochodzący wprost z ekologicznych upraw w Ekwadorze', tags: 'zółty słodki owoc', img: '/images/Donald-duck.png', price: "4", id: '1' },
            { name: 'marchewka', desc: 'pomarańczowe słodkawe warzywo pochodzące wprost z ekologicznych upraw z Podkarpacia', tags: 'pomawańczowe słodkawe warzywo', img: '/images/Donald-duck.png', price: "3", id: '2' }
        ],
        user: 'Gosia'
    });
});
app.use('/admin', (req, res, next) => {
    res.render('admin_view.ejs', {
        products: [
            { name: 'banan', desc: 'zółty słodki owoc pochodzący wprost z ekologicznych upraw w Ekwadorze', tags: 'zółty słodki owoc', img: '/images/Donald-duck.png', price: "4", id: '1' },
            { name: 'marchewka', desc: 'pomarańczowe słodkawe warzywo pochodzące wprost z ekologicznych upraw z Podkarpacia', tags: 'pomawańczowe słodkawe warzywo', img: '/images/Donald-duck.png', price: "3", id: '2' }
        ],
        admin: 'Gosia'
    });
});
app.use((req, res, next) => {
    res.render('main_view.ejs', {
        products: [
            { name: 'banan', desc: 'zółty słodki owoc pochodzący wprost z ekologicznych upraw w Ekwadorze', tags: 'zółty słodki owoc', img: '/images/Donald-duck.png', price: "4" },
            { name: 'marchewka', desc: 'pomarańczowe słodkawe warzywo pochodzące wprost z ekologicznych upraw z Podkarpacia', tags: 'pomawańczowe słodkawe warzywo', img: '/images/Donald-duck.png', price: "3" }
        ]
    });
});
http.createServer(app).listen(3000);
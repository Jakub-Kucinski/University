// const config = require('config');
// const Joi = require('joi');
const express = require('express');
const app = express();

app.use(express.json());

// console.log('App name: ' + config.get('name'));

const port = process.env.PORT || 3000;
app.listen(port, () => {
    console.log(`Listening on port ${port}`);
});

const courses = [
  { id: 1, name: 'elo' },
  { id: 2, name: 'lo' },
  { id: 3, name: 'o' },
];

//ODCZYTYWANIE DANYCH
app.get('/api/courses/:id', (req, res) => {
    const course = courses.find(c => c.id === parseInt(req.params.id));
    if (!course) return res.status(404).send('The course with the given id was not found');
    res.send(course);
});
app.get("/api/courses/", (req, res) => {
    res.send(courses);
});

//WPROWADZANIE DANYCH
app.post('/api/courses/', (req, res) => {
    // const { error } = validateCourse(req.body);
    // if (error) return res.status(400).send(error.details[0].message);


    const course = {
        id: courses.length + 1,
        name: req.params.name
    };
    courses.push(course);
    res.send(course);
});


//ZMIENIANIE DANYCH / PRZESYŁANIE DANYCH NA SERWER W CELU UPDATEOWANIA
app.put('/api/courses/:id', (req, res) => {
    const course = courses.find(c => c.id === parseInt(req.params.id));
    if (!course) return res.status(404).send('The course with the given id was not found');

    // const {error} = validateCourse(req.body);
    // if (error) return res.status(400).send(error.details[0].message);

    course.name = req.body.name;
    res.send(course);
});

// function validateCourse(course){
//     const schema = { name: Joi.string()
//         .min(3)
//         .required() };
//     return Joi.validate(course, schema);
    
// }

//USUWANIE DANYCH
app.delete("/api/courses/:id", (req, res) =>{
    const course = courses.find(c => c.id === parseInt(req.params.id));
    if (!course) return res.status(404).send("The course with the given id was not found");
    const index = courses.indexOf(course);
    courses.splice(index, 1);
    res.send(course);
});


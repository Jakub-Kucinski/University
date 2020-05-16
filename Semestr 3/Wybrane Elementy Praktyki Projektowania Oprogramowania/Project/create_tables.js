const bcrypt = require('bcryptjs');


const Pool = require('pg').Pool
const pool = new Pool({
  user: 'postgres',
  host: 'localhost',
  database: 'online_shop',
  password: 'postgres',
  port: 5432,
})


async function create_user_table() {
    await pool.query("CREATE TABLE IF NOT EXISTS User_account ( \
        user_id SERIAL PRIMARY KEY, \
        login VARCHAR(100) UNIQUE NOT NULL, \
        password VARCHAR(100) NOT NULL \
        );", (error, results) => {
            if (error) {
                throw error;
            }
            console.log("User table created successfully");
    })
}

async function create_admin_table() {
    await pool.query("CREATE TABLE IF NOT EXISTS Admin ( \
        admin_id SERIAL PRIMARY KEY, \
        login VARCHAR(100) UNIQUE NOT NULL, \
        password VARCHAR(100) NOT NULL \
        );", (error, results) => {
            if (error) {
                throw error;
            }
            console.log("Admin table created successfully");
    })
}

async function create_product_table() {
    await pool.query("CREATE TABLE IF NOT EXISTS Product ( \
        product_id SERIAL PRIMARY KEY, \
        name VARCHAR(100) NOT NULL, \
        tags VARCHAR(200), \
        price DECIMAL(18, 3) CHECK(price > 0), \
        link VARCHAR(100), \
        description TEXT \
        );", (error, results) => {
            if (error) {
                throw error;
            }
            console.log("Product table created successfully");
    })
}

async function create_basket_table() {
    await pool.query("CREATE TABLE IF NOT EXISTS Basket ( \
        user_id integer REFERENCES User_account (user_id), \
        product_id integer REFERENCES Product (product_id), \
        amount DECIMAL(18, 3) \
        );", (error, results) => {
            if (error) {
                throw error;
            }
            console.log("Basket table created successfully");
    })
}

async function create_ordered_table() {
    await pool.query("CREATE TABLE IF NOT EXISTS Ordered ( \
        user_id integer REFERENCES User_account (user_id), \
        product_id integer REFERENCES Product (product_id), \
        date_of_order timestamp, \
        price DECIMAL(18, 3) CHECK(price > 0), \
        amount DECIMAL(18, 3) \
        );", (error, results) => {
            if (error) {
                throw error;
            }
            console.log("Ordered table created successfully");
    })
}

async function create_all_tables() {
    await create_user_table();
    await create_admin_table();
    await create_product_table();
    await create_basket_table();
    await create_ordered_table();
}


// var salt = bcrypt.genSaltSync(10);
// var hash = bcrypt.hashSync("śćłó", salt);
// var salt2 = bcrypt.genSaltSync(10);
// var hash2 = bcrypt.hashSync("śćłó", salt2);
// console.log(salt, " ", hash, " ", salt2, " ", hash2, "\n");

// var t = bcrypt.compareSync("śćłó", hash); // true
// bcrypt.compareSync("not_bacon", hash); // false
// console.log(t);

create_all_tables();
// create_user_table();
// create_admin_table();
// create_product_table();
// create_basket_table();
// create_order_table();

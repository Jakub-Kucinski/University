const bcrypt = require('bcryptjs');

const Pool = require('pg').Pool
const pool = new Pool({
  user: 'postgres',
  host: 'localhost',
  database: 'online_shop',
  password: 'postgres',
  port: 5432,
})

// Function as arguments takes two strings, login and password for new user. If user with same login
// already exists, returns null, otherwise returns id of the new added user.
// In case of same sql or connection error, throws an error.
async function register_new_user(login, password) {
  try {
    var res = await pool.query("SELECT User_account.user_id \
      FROM User_account \
      WHERE User_account.login LIKE $1 ;", [login]);
    if (res.rowCount === 0) {
      var salt = bcrypt.genSaltSync(10);
      var hash = bcrypt.hashSync(password, salt);
      var res2 = await pool.query("INSERT INTO User_account (login, password) \
      VALUES ($1, $2) RETURNING User_account.user_id", [login, hash]);
      return res2.rows[0].user_id;
    } else {
      return null;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}

// Function as arguments takes two strings, login and password of user to log in. 
// If user with given login exists and password is correct, returns id of this user, otherwise retruns null.
// In case of same sql or connection error, throws an error.
async function log_in_user(login, password) {
  try {
    var res = await pool.query("SELECT User_account.user_id, User_account.password \
      FROM User_account \
      WHERE User_account.login LIKE $1 ;", [login]);
    if (res.rowCount === 1 && bcrypt.compareSync(password, res.rows[0].password)) {
      return res.rows[0].user_id;
    } else {
      return null;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}

async function register_new_admin(login, password) {
  try {
    var res = await pool.query("SELECT Admin.admin_id \
      FROM Admin \
      WHERE Admin.login LIKE $1 ;", [login]);
    if (res.rowCount === 0) {
      var salt = bcrypt.genSaltSync(10);
      var hash = bcrypt.hashSync(password, salt);
      var res2 = await pool.query("INSERT INTO Admin (login, password) \
      VALUES ($1, $2) RETURNING Admin.admin_id", [login, hash]);
      return res2.rows[0].admin_id;
    } else {
      return null;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}

async function log_in_admin(login, password) {
  try {
    var res = await pool.query("SELECT Admin.admin_id, Admin.password \
      FROM Admin \
      WHERE Admin.login LIKE $1 ;", [login]);
    if (res.rowCount === 1 && bcrypt.compareSync(password, res.rows[0].password)) {
      return res.rows[0].admin_id;
    } else {
      return null;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}


// Function as arguments takes string:: name, string:: tags, float::price, string:: link, string:: description. 
// Adds new product with given as function arguments paramethers. Returns id of added product.
// In case of same sql or connection error, throws an error.
async function add_new_product(name, tags, price, link, description) {
  try {
    var res = await pool.query("INSERT INTO Product (name, tags, price, link, description) \
    VALUES ($1, $2, $3, $4, $5) RETURNING Product.product_id",
      [name, tags, price, link, description]);
    return res.rows[0].product_id;
  } catch(err) {
    console.log(err);
    throw err;
  }
}


// Function as arguments takes int:: product_id, string:: name, string:: tags, float::price, string:: link, string:: description. 
// Modify existing product of given product_id with paramethers from function arguments. If one exists, returns id of modified product.
// Otherwise returns null. In case of same sql or connection error, throws an error.
async function modify_product(product_id, name, tags, price, link, description) {
  try {
    var res = await pool.query("UPDATE Product \
    SET name = $1, tags = $2, price = $3, link = $4, description = $5 \
    WHERE Product.product_id = $6 RETURNING Product.product_id",
      [name, tags, price, link, description, product_id]);
    if (res.rowCount === 1) {
      return res.rows[0].product_id;
    } else {
      return null;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}

// Function as arguments takes int:: product_id. 
// If product of given product_id exists, deletes it and returns its id, otherwise returns null.
// In case of same sql or connection error, throws an error.
async function delete_product(product_id) {
  try {
    var res = await pool.query("DELETE FROM Product \
    WHERE Product.product_id = $1 RETURNING Product.product_id", [product_id]);
    if (res.rowCount === 1) {
      return res.rows[0].product_id;
    } else {
      return null;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}

// Function as arguments takes string:: filter_phrase. 
// Returns list of object in shape { product_id: 1, name: "name of prod", tags: "tag1 tag2 tag3",
// price: 1.000, link: "link to image", description: "info about product"}, where each attribute "name" comprise filter_phrase.
// In case of same sql or connection error, throws an error.
async function list_of_products_filter_name(filter_phrase) {
  try {
    var res = await pool.query("SELECT * FROM Product \
    WHERE Product.name LIKE $1", ['%'+filter_phrase+'%']);
    return res.rows;
  } catch(err) {
    console.log(err);
    throw err;
  }
}

// Function as arguments takes string:: filter_phrase. 
// Returns list of object in shape { product_id: 1, name: "name of prod", tags: "tag1 tag2 tag3",
// price: 1.000, link: "link to image", description: "info about product"}, where each attribute "tags" comprise filter_phrase.
// In case of same sql or connection error, throws an error.
async function list_of_products_filter_tags(filter_phrase) {
  try {
    var res = await pool.query("SELECT * FROM Product \
    WHERE Product.tags LIKE $1", ['%'+filter_phrase+'%']);
    return res.rows;
  } catch(err) {
    console.log(err);
    throw err;
  }
}


async function add_product_to_basket(user_id, product_id) {
  try {
    var res = await pool.query("SELECT * FROM Basket \
    WHERE Basket.user_id = $1 AND Basket.product_id = $2", [user_id, product_id]);

    if (res.rowCount === 0) {
      var res2 = await pool.query("INSERT INTO Basket (user_id, product_id, amount) \
      VALUES ($1, $2, 1) RETURNING Basket.user_id, Basket.product_id, Basket.amount ",
        [user_id, product_id]);
      return res2.rows[0];
    } else {
      amount = 1 + parseFloat(res.rows[0].amount);
      var res3 = await pool.query("UPDATE Basket \
      SET amount = $1 \
      WHERE Basket.user_id = $2 AND Basket.product_id = $3 \
      RETURNING Basket.user_id, Basket.product_id, Basket.amount ",
        [amount, user_id, product_id]);
      return res3.rows[0];
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}


async function add_product_to_basket_amount(user_id, product_id, amount) {
  try {
    var res = await pool.query("SELECT * FROM Basket \
    WHERE Basket.user_id = $1 AND Basket.product_id = $2", [user_id, product_id]);
    if (res.rowCount === 0) {
      var res2 = await pool.query("INSERT INTO Basket (user_id, product_id, amount) \
      VALUES ($1, $2, $3) RETURNING Basket.user_id, Basket.product_id, Basket.amount ",
        [user_id, product_id, amount]);
      return res2.rows[0];
    } else {
      new_amount = amount + parseFloat(res.rows[0].amount);
      var res3 = await pool.query("UPDATE Basket \
      SET amount = $1 \
      WHERE Basket.user_id = $2 AND Basket.product_id = $3 \
      RETURNING Basket.user_id, Basket.product_id, Basket.amount ",
        [new_amount, user_id, product_id]);
      return res3.rows[0];
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}


async function set_product_in_basket_amount(user_id, product_id, amount) {
  try {
    var res = await pool.query("SELECT * FROM Basket \
    WHERE Basket.user_id = $1 AND Basket.product_id = $2", [user_id, product_id]);
    if (res.rowCount === 0) {
      var res2 = await pool.query("INSERT INTO Basket (user_id, product_id, amount) \
      VALUES ($1, $2, $3) RETURNING Basket.user_id, Basket.product_id, Basket.amount ",
        [user_id, product_id, amount]);
      return res2.rows[0];
    } else {
      var res3 = await pool.query("UPDATE Basket \
      SET amount = $1 \
      WHERE Basket.user_id = $2 AND Basket.product_id = $3 \
      RETURNING Basket.user_id, Basket.product_id, Basket.amount ",
        [amount, user_id, product_id]);
      return res3.rows[0];
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}



async function remove_product_from_basket(user_id, product_id) {
  try {
    var res = await pool.query("DELETE FROM Basket \
    WHERE Basket.user_id = $1 AND Basket.product_id = $2 \
    RETURNING Basket.user_id, Basket.product_id, Basket.amount", [user_id, product_id]);
    if (res.rowCount === 0) {
      return null;
    } else {
      return res.rows[0];
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}


async function make_order(user_id) {
  try {
    var res = await pool.query("DELETE FROM Basket \
    WHERE Basket.user_id = $1 \
    RETURNING Basket.user_id, Basket.product_id, Basket.amount", [user_id]);
    if (res.rowCount === 0) {
      return null;
    } else {
      var t = [];
      var n = res.rowCount;
      for (var i = 0; i < n; i++) {
        row = res.rows[i];
        var res2 = await pool.query("SELECT Product.price FROM Product \
        WHERE Product.product_id = $1", [row.product_id]);
        var price = res2.rows[0].price;
        var res3 = await pool.query("INSERT INTO Ordered (user_id, product_id, date_of_order, price, amount) \
        VALUES ($1, $2, NOW(), $3, $4) RETURNING user_id, product_id, date_of_order, price, amount",
          [row.user_id, row.product_id, price, row.amount]);
        t.push(res3.rows[0]);
      }
      return t;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}

async function user_orders_list(user_id) {
  try {
    var res = await pool.query("SELECT * FROM Ordered \
    WHERE Ordered.user_id = $1", [user_id]);
    if (res.rowCount === 0) {
      return null;
    } else {
      return res.rows;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}

async function users_list() {
  try {
    var res = await pool.query("SELECT User_account.user_id, User_account.login FROM User_account");
    if (res.rowCount === 0) {
      return null;
    } else {
      return res.rows;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}


async function orders_list() {
  try {
    var res = await pool.query("SELECT * FROM Ordered ORDER BY Ordered.date_of_order DESC");
    if (res.rowCount === 0) {
      return null;
    } else {
      return res.rows;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}


async function baskets_list() {
  try {
    var res = await pool.query("SELECT * FROM Basket ORDER BY Basket.user_id");
    if (res.rowCount === 0) {
      return null;
    } else {
      return res.rows;
    }
  } catch(err) {
    console.log(err);
    throw err;
  }
}


// TO DO
// backets_lists_grouped_by_users
// orders_lists_grouped_by_users
// user_basket_list_describe
// user_orders_list_describe
// backets_list_describe
// orders_list_describe
// backets_lists_describe_grouped_by_users
// orders_lists_describe_grouped_by_users

async function main() {
  // wynik = await register_new_user("moj_login5", "moje_haslo");
  // console.log(wynik);
  // wynik2 = await log_in_user("moj_login5", "moje_haslo");
  // console.log(wynik2);
  wynik35 = await register_new_admin("admin", "admin");
  console.log(wynik35);
  // wynik3 = await add_new_product("banan", "żółty złodki owoc", 4, "link do obrazka",
  //   "Żółty słodki owoc pochodzący wprost z ekologicznych upraw w Ekwadorze");
  // console.log(wynik3);
  // wynik4 = await modify_product(1, "lepszy banan", "żółty złodki owoc", 4, "link do obrazka",
  //   "Żółty słodki owoc pochodzący wprost z ekologicznych upraw w Ekwadorze");
  // console.log(wynik4);
  // wynik5 = await delete_product(2);
  // console.log(wynik5);
  // wynik6 = await list_of_products_filter_name("y b");
  // console.log(wynik6);
  // wynik65 = await list_of_products_filter_name("");
  // console.log(wynik65);
  // wynik7 = await list_of_products_filter_tags("łodki");
  // console.log(wynik7);
  // wynik8 = await add_product_to_basket(5, 3);
  // console.log(wynik8);
  // wynik9 = await add_product_to_basket_amount(6, 3, 10);
  // console.log(wynik9);
  // wynik10 = await set_product_in_basket_amount(5, 1, 23);
  // console.log(wynik10);
  // wynik11 = await remove_product_from_basket(4, 3);
  // console.log(wynik11);
  // wynik12 = await make_order(5);
  // console.log(wynik12);
  // wynik13 = await user_orders_list(5);
  // console.log(wynik13);
  // wynik14 = await users_list();
  // console.log(wynik14);
  // wynik15 = await orders_list();
  // console.log(wynik15);
  // wynik16 = await baskets_list();
  // console.log(wynik16);

}

main();

module.exports = {
  bcrypt, Pool, pool, register_new_user, log_in_user, log_in_admin, add_new_product, modify_product, delete_product,
  list_of_products_filter_name, list_of_products_filter_tags, add_product_to_basket, add_product_to_basket_amount, set_product_in_basket_amount,
  remove_product_from_basket, make_order, user_orders_list, users_list, orders_list, baskets_list
};
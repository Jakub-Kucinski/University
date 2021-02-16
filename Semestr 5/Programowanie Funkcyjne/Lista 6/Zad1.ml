let rec fix f x = f (fix f) x;;

let fib_f fib n =
    if n <= 1 then n
    else fib (n-1) + fib (n-2);;

let fib = fix fib_f;;

exception Max_depth;;

let rec fix_with_limit n f x = if n > 0  then f (fix_with_limit (n-1) f) x else raise Max_depth;;

let fib_with_limit = fix_with_limit 10 fib_f;;

let fix_memo f = 
    let tbl = Hashtbl.create 100 
        in let rec foo f x =
            try Hashtbl.find tbl x
            with Not_found -> let new_value = f (foo f) x in Hashtbl.add tbl x new_value; new_value
            in fun x -> foo f x;;

let fib_memo = fix_memo fib_f;;

fib 10;;

fib_with_limit 10;;

fib_with_limit 20;;

fib_memo 10;;
fib_memo 100000;;
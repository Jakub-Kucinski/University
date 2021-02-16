let rec fix f x = f (fix f) x;;

let fib_f fib n =
    if n <= 1 then n
    else fib (n-1) + fib (n-2);;

let fib = fix fib_f;;


type 'a fix = Fix of ('a fix -> 'a);;

let fix big_fun = 
    let p = fun ((Fix f) as fixed_f) x -> big_fun (f fixed_f) x 
    in p (Fix p);;

let fix_magic (f: ('a -> 'b) -> 'a -> 'b) : 'a -> 'b = Obj.magic;; 
let fix_magic = ref fix_magic;;
let fix2 f x = f (!fix_magic f) x;;
fix_magic := fix2;;
let fib2 = fix2 fib_f;;


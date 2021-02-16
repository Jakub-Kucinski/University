type 'a lazylist = LazyNil | LazyCons of 'a * 'a lazylist Lazy.t;;

let lazy_elements = 
    let rec foo k sign = 
        LazyCons(1.0 /. k *. sign, lazy (foo (k+.2.0) (sign *. (-1.0))) )
    in foo 1.0 1.0;;

let lazy_aprox_pi n =
    let stream = lazy_elements
        in let rec foo (n, str) = 
            match (n, str) with
            | (0, _) -> 0.0
            | (k, LazyCons(x, lazy xf)) -> x +. (foo (k-1, xf))
        in 4.0 *. (foo (n, stream));;

let lazy_aprox_stream = 
    let rec foo k sign value = 
        LazyCons(4.0 /. k *. sign +. value, lazy (foo (k+.2.0) (sign *. (-1.0)) (4.0 /. k *. sign +. value))) 
    in foo 1.0 1.0 0.0;;

let rec lazy_take(n, lxs) = match(n, lxs) with 
    (0, _) -> []
    | (_, LazyNil) -> []
    | (n, LazyCons(x, lazy xf)) -> x::lazy_take(n-1, xf);;


let rec transform_triple f lxs = 
    match lxs with
    | LazyCons(x1, lazy (LazyCons(x2, lazy (LazyCons(x3, lazy xf))))) -> 
        LazyCons(f x1 x2 x3, lazy(transform_triple f (LazyCons(x2, (lazy (LazyCons(x3, lazy xf)))))))
    | _ -> LazyNil;;

let rec lfrom k = LazyCons (k, lazy (lfrom (k+1)));; 

let euler_transform x y z = z -. ((y-.z)*.(y-.z))/.(x -. 2.0*.y +. z);;

let test = transform_triple (fun x1 x2 x3 -> x1+x2+x3) (lfrom 0);;
lazy_take(10, test);;

let faster_pi_aprox_stream = transform_triple euler_transform lazy_aprox_stream;;
lazy_take(10, faster_pi_aprox_stream);;
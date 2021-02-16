(* (’a -> ’b -> (’a -> ’c) -> ’c) -> ’a -> ’b list -> (’a -> ’c) -> ’c *)
(* let rec fold_left_cps fcps acc xs k =
    match xs with
    | [] -> k acc
    | y::ys -> fold_left_cps fcps acc ys (fun v -> fcps v y k);; *)
(* let fold_left f acc xs = fold_left_cps (fun acc x k -> k (f acc x)) acc xs (fun x -> x);; *)

let rec fold_left_cps fcps acc xs k =
    match xs with
    | [] -> k acc
    | h::t -> f acc h (fun x -> fold_left_cps f x t k) ;;
    

let fold_left f acc xs = fold_left_cps (fun acc x k -> k (f acc x)) acc xs (fun x -> x);;

let rev = fold_left (fun acc x -> x::acc) [];;
rev [1;2;3;4];;
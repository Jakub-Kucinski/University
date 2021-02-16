type 'a clist = {clist : 'z. ('a -> 'z -> 'z) -> 'z -> 'z};;

let compose f g x y = f (g(x)) y;;

let cnil = {clist = fun f x -> x};;
let ccons a cl = {clist = fun f x -> f a ((cl.clist f) x)};;
let is_cnil cl = cl.clist (fun f x -> false) true;;
let map g cl = {clist = fun f x ->  cl.clist (compose f g) x};;
let append cl1 cl2 = {clist = fun f x -> (cl1.clist f) ((cl2.clist f) x)};;
let prod cl1 cl2 = {clist = fun f x -> cl1.clist (fun a -> cl2.clist (fun b -> f (a,b) )) x};;
let clist_to_list cl = cl.clist (fun a z -> a::z) [];;
let rec clist_of_list l =
    match l with
    [] -> cnil
    | x::xs -> ccons x (clist_of_list xs);;

let l1 = [1;2;3;4;5];;
let l2 = [6;7;8];;
clist_to_list (map (fun x -> x+1) (ccons 0 (append (clist_of_list l1) (clist_of_list l2))));;
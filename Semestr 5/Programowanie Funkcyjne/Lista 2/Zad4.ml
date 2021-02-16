let rec map f list = 
    match list with
    [] -> []
    | x::xs -> (f x)::(map f xs);;

let rec insert a list =
  match list with
  [] -> [[a]]
  | x::xs -> 
    (a::list) :: (map (fun l -> x::l) (insert a xs));;

let flatten list =
  let rec loop l acc =
    match l with
    [] -> acc
    | x::xs -> loop xs (acc @ x)
  in loop list [];;

let rec perm list =
  match list with
  [] -> [[]]
  | h::t -> 
    flatten (map (insert h) (perm t));;

perm [0;1;2];;
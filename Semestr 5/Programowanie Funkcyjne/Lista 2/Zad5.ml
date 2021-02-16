let rec suffixes list = 
    match list with
    [] -> [[]]
    | x::xs -> let res = suffixes xs in (x::(List.hd res))::res;;

let reverse list =
    let rec loop l1 acc = 
        match l1 with
        [] -> acc
        | x::xs -> loop xs (x::acc)
    in loop list [];;

let rec map f list = 
    match list with
    [] -> []
    | x::xs -> (f x)::(map f xs);;

let prefixes list = reverse (map reverse (suffixes (reverse list)));;

suffixes [1;2;3];;
prefixes [1;2;3];;
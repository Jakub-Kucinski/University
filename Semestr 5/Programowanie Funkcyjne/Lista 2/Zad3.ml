let rec merge cmp l1 l2 = match (l1, l2) with
    (xs, []) -> xs
    | ([], ys) -> ys
    | (x::xs, y::ys) -> if cmp x y 
                        then x::(merge cmp xs (y::ys)) 
                        else y::(merge cmp (x::xs) ys);;

let reverse l1 = 
    let rec loop list acc =
        match list with
        x::xs -> loop xs (x::acc)
        | [] -> acc
        in loop l1 [];;

let merge2 cmp l1 l2 = 
    let rec loop cmp list1 list2 acc =
        match (list1, list2) with
        ([], []) -> acc
        | (x::xs, []) -> loop cmp xs [] (x::acc)
        | ([], y::ys) -> loop cmp [] ys (y::acc)
        | (x::xs, y::ys) -> if cmp x y
                            then loop cmp list1 ys (y::acc)
                            else loop cmp xs list2 (x::acc)
        in loop cmp (reverse l1) (reverse l2) [];;

let halve l1 = 
    let rec f list1 list2 list =
        match list with
        [] -> (list1, list2)
        | x::[] -> (list1, x::list2)
        | x1::x2::xs -> f (x1::list1) (x2::list2) xs
    in f [] [] l1;;

let rec mergesort cmp l1 =
    match l1 with
    [] -> []
    | x::[] -> x::[]
    | _ -> let (list1, list2) = halve l1 in merge2 cmp (mergesort cmp list1) (mergesort cmp list2);;

let merge3 cmp l1 l2 rev = 
  let rec ordered_merge cmp list1 list2 reversed acc = 
    match (list1, list2, reversed) with
    ([], [], _) -> acc
    | (x::xs, [], _) -> ordered_merge cmp xs [] reversed (x::acc)
    | ([], y::ys, _) -> ordered_merge cmp [] ys reversed (y::acc)
    | (x::xs, y::ys, false) -> if cmp x y 
                               then ordered_merge cmp xs list2 reversed (x::acc)
                               else ordered_merge cmp list1 ys reversed (y::acc)
    | (x::xs, y::ys, true) -> if cmp x y 
                              then ordered_merge cmp list1 ys reversed (y::acc)
                              else ordered_merge cmp xs list2 reversed (x::acc)
    in ordered_merge cmp l1 l2 rev [];;

let mergesort2 cmp list = 
  let rec inner_mergesort cmp list reversed = 
  match list with
    []  -> []
  | x::[] -> list
  | _ -> let (list1, list2) = halve list in 
                merge3 cmp 
                    (inner_mergesort cmp list1 (not reversed)) 
                    (inner_mergesort cmp list2 (not reversed)) 
                    reversed
  in inner_mergesort cmp list true;;

merge3 (<=) [1;2;5] [3;4;5] false;;
merge3 (<=) [5;2;1] [5;4;3] true;;
mergesort2 (<=) [2;5;4;8;5;6;0;2;1;4];;

merge (<=) [1;2;3] [1;2;3];;
merge2 (<=) [1;2;3] [1;2;3];;
merge (<=) [1; 2; 5] [3; 4; 5] = [1; 2; 3; 4; 5; 5];;
merge2 (<=) [1; 2; 5] [3; 4; 5] = [1; 2; 3; 4; 5; 5];;
mergesort (<=) [9;5;8;2;4;6;1;0;3;7];;
let length = List.fold_left (fun acc x -> acc+1) 0;;
length [1;2;3;4];;

let rev = List.fold_left (fun acc x -> x::acc) [];;
rev [1;2;3;4];;

let map f xs = List.fold_right (fun x acc -> (f x)::acc) xs [];;
map (fun x -> 5+x) [1;2;3;4];;

let append xs ys = List.fold_right (fun x acc -> x::acc) xs ys;;
append [1;2;3;4] [5;6;7;8];;

let rev_append xs ys = List.fold_left (fun acc x -> x::acc) ys xs;;
rev_append [1;2;3;4] [5;6;7;8];;

let filter f xs = List.fold_right (fun x acc -> if f x then x::acc else acc) xs [];;
filter (fun x -> x mod 2 = 1) [1;2;3;4];;

let rev_map f xs = List.fold_left (fun acc x -> (f x)::acc) [] xs;;
rev_map (fun x -> 5+x) [1;2;3;4];;

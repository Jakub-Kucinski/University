let rec fold_left_cps fcps acc xs k =
    match xs with
    | [] -> k acc
    | h::t -> fcps acc h (fun x -> fold_left_cps fcps x t k) ;;

let for_all f xs = fold_left_cps (fun acc x k -> f x && k acc) true xs (fun x -> x);;
for_all (fun x -> x mod 2 = 0) [2;4;6];;
for_all (fun x -> x mod 2 = 0) [2;5;6];;

let mult_list xs = fold_left_cps (fun acc x k -> if x = 0 then 0 else k (acc * x)) 1 xs (fun x -> x);;
mult_list [1;2;3;4;5];;
mult_list [1;2;0;4;5];;

let sorted xs = 
    match xs with
    | [] -> true
    | y::ys -> snd (fold_left_cps (fun (acc, bl) x k -> if acc <= x
                                                        then k (x, true)
                                                        else (x, false)) 
                                  (y, true) 
                                  xs
                                  (fun x -> x));;

sorted [1;2;3;4];;
sorted [1;2;2;3;4];;
sorted [1;1;2;3;4];;
sorted [1;3;2;4];;

(* let rec list_of_pairs xs = 
    match xs with
    | [] -> []
    | y::[] -> []
    | y1::y2::ys -> (y1, y2) :: (list_of_pairs (y2::ys));;

let sorted2 xs = fold_left_cps (fun acc (x, y) k -> x <= y && k acc) true (list_of_pairs xs) (fun x -> x);;

sorted2 [1;2;3;4];;
sorted2 [1;2;2;3;4];;
sorted2 [1;1;2;3;4];;
sorted2 [1;3;2;4];; *)
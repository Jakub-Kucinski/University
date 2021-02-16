exception False_value;;
let for_all f xs =  try List.fold_left (fun acc x -> if f x 
                                                     then acc 
                                                     else raise False_value) 
                                        true 
                                        xs  
                    with False_value -> false;;

for_all (fun x -> x mod 2 = 0) [2;4;6;8;10];;
for_all (fun x -> x mod 2 = 0) [2;4;5;8;10];;

exception Zero_factor;;
let mult_list xs = try List.fold_left (fun acc x -> if x = 0
                                                    then raise Zero_factor
                                                    else x * acc)
                                      1
                                      xs
                   with Zero_factor -> 0;; 

mult_list [1;2;3;4;5];;
mult_list [1;2;0;4;5];;

exception Descending_order;;
let sorted xs = 
    match xs with
    | [] -> true
    | y::ys -> try snd ((List.fold_left (fun acc x -> if acc <= x
                                                      then x
                                                      else raise Descending_order) 
                                  y 
                                  xs), 
                        true)
               with Descending_order -> false;;

sorted [1;2;3;4];;
sorted [1;2;2;3;4];;
sorted [1;1;2;3;4];;
sorted [1;3;2;4];;

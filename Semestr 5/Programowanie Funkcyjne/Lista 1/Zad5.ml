(* Jakub Kucinski, grupa efes *)

let zero = fun f -> (fun x -> x);;

let succ bigf f x = f ((bigf f) x);;

let add bigf bigg f x = (bigf f) ((bigg f) x);;

let mul bigf bigg f x = (bigf (bigg f)) x ;;

let is_zero bigf = bigf (fun x -> false) true;;

let cnum_of_int n =  let rec test i acc = if i = n
                                          then acc
                                          else test (i + 1) (succ acc)
                                         in test 0 zero;;

let int_of_cnum bigf = (bigf (fun x -> x + 1)) 0;;

                       
let n5 = 5;;
let c5 = cnum_of_int n5;;
int_of_cnum c5;;
int_of_cnum zero;;
let n7 = 7;;
let c7 = cnum_of_int n7;;
let c35 = mul c5 c7;;
int_of_cnum c35;;
let c12 = add c5 c7;;
int_of_cnum c12;;

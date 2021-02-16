(* Jakub Kucinski, grupa efes *)
fun x -> x;;
fun x -> 0+x;;

fun f g x -> f (g(x));;

fun x y -> x;;

fun x y -> if x > y then x else y;;

fun x -> raise (Failure "err");;



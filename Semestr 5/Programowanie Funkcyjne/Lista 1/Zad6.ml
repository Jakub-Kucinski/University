(* Jakub Kucinski, grupa efes *)

type cbool = { cbool : 'a. 'a -> 'a -> 'a } ;;
type cnum = { cnum : 'a. ('a -> 'a) -> 'a -> 'a } ;;

let even n = {cbool = fun tt ff -> fst (n.cnum (fun (a, b) -> (b, a)) (tt, ff)) };;

let ctrue = {cbool = fun x y -> if x > y then x else y};;
let cfalse = {cbool = fun x y -> if x > y then y else x};;

let cor c1 c2 = {cbool = fun x y -> if c1.cbool x y > c2.cbool x y 
                                    then c1.cbool x y else c2.cbool x y};;
let cand c1 c2 = {cbool = fun x y -> if c1.cbool x y < c2.cbool x y 
                                    then c1.cbool x y else c2.cbool x y};;

let cbool_of_bool b = {cbool = if b then ctrue.cbool else cfalse.cbool};;
let bool_of_cbool cb = if cb.cbool true false = true then true else false;;

bool_of_cbool (cor cfalse cfalse);;
bool_of_cbool (cor cfalse ctrue);;
bool_of_cbool (cor ctrue cfalse);;
bool_of_cbool (cor ctrue ctrue);;
bool_of_cbool (cand cfalse cfalse);;
bool_of_cbool (cand cfalse ctrue);;
bool_of_cbool (cand ctrue cfalse);;
bool_of_cbool (cand ctrue ctrue);;

let zero = {cnum = fun f -> (fun x -> x)};;

let succ bigf = {cnum = fun f x -> f ((bigf.cnum f) x)};;

let add bigf bigg = {cnum = fun f x -> (bigf.cnum f) ((bigg.cnum f) x)};;

let mul bigf bigg = {cnum = fun f x -> (bigf.cnum (bigg.cnum f)) x};;

let is_zero bigf = bigf.cnum (fun x -> false) true;;

let cnum_of_int n = {cnum = (let rec test i acc = if i = n
                                          then acc
                                          else test (i + 1) (succ acc)
                                         in test 0 zero)};;

let int_of_cnum bigf = (bigf.cnum (fun x -> x + 1)) 0;;

(*                        
let n5 = 5;;
let c5 = cnum_of_int n5;;
int_of_cnum c5;;
int_of_cnum zero;;
let n7 = 7;;
let c7 = cnum_of_int n7;;
let c35 = mul c5 c7;;
int_of_cnum c35;;
let c12 = add c5 c7;;
int_of_cnum c12;; *)

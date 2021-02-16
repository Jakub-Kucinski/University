(* Jakub Kucinski, grupa efes *)

let hd s = s 0;;
let tl s = fun x -> s (x + 1);;
let add s c = fun x -> s x + c;;
let map s f = fun x -> f (s x);;
let map2 s1 s2 f = fun x -> f (s1 x) (s2 x);;
let replace s n a = fun x -> if x mod n = 0 then a else s x;;
let take s n = fun x -> s (x * n);;
let scan f s a = fun x -> (let rec test i acc = if i = x
                                                then f acc (s x)
                                                else test (i+1) (f acc (s i)) in test 0 a);;
let tabulate s ?(a=0) b = let rec test i acc = if i = a
                                               then (s a)::acc
                                               else test (i - 1) ((s i)::acc) in test b [];;
let series1 x = x+0;;
let series2 x = x*2;;
let s1 = series1;;
let s2 = series2;;

hd s1;;
hd s2;;

(tl s1) 0;;
(tl s2) 0;;

(add s1 10) 5;;
(add s2 10) 5;;

(map s1 (fun x -> 10*x)) 5;;
(map s2 (fun x -> 10*x)) 5;;

(map2 s1 s2 (fun x y -> x + y)) 5;;

(replace s1 5 100) 5;;
(replace s1 5 100) 6;;

(take s1 5) 5;;
(take s1 5) 6;;

let s3 = scan (fun x y -> x + y) s1 0;;
s3 0;;
s3 1;;
s3 2;;
s3 3;;

(tabulate s1 10);;
(tabulate s2 10);;
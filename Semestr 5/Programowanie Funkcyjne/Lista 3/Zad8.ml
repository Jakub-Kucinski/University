open Proc;;
let rec echo k = recv (fun v -> send v (fun () -> echo k));;

let rec map f k = recv (fun v -> send (f v) (fun () -> map f k));;

let rec filter pred k = recv (fun v -> if pred v then send v (fun () -> filter pred k) else filter pred k);;

let rec nats_from k =
    let rec foo n k =
        send (string_of_int n) (fun () -> foo (n+1) k)
    in recv (fun v -> foo (int_of_string v) k);;

let rec nats_from n k = send n (fun () -> nats_from (n+1) k);;

let rec sieve k = recv (fun v -> send v (fun() -> (filter (fun x -> x mod v <> 0) <|>> sieve) k));;

run (nats_from 2 <|>> sieve <|>> map string_of_int);;
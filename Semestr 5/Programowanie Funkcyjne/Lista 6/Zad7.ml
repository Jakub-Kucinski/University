type 'a my_lazy = {lazy_fun: (unit -> 'a); mutable value: 'a option; mutable is_calculating: bool}

let force (lval: 'a my_lazy) =
    if lval.is_calculating then
        match lval.value with
        | None -> failwith("not productive")
        | Some arg -> arg
    else
        (
            lval.is_calculating <-  true;
            let res = (lval.lazy_fun ()) 
                in lval.value <- Some res; res
        )

let rec fix (f: 'a my_lazy -> 'a) : 'a my_lazy =
    let rec res = {lazy_fun = (fun () -> f res) ; value = None; is_calculating = false} in res

type 'a lstream = Cons of 'a * ('a lstream) my_lazy
let rec my_ltake n lxs =
  match (n, force lxs) with
  | 0, _ -> []
  | n, Cons (x, xf) -> x :: my_ltake (n - 1) xf

let stream_of_ones = fix (fun stream_of_ones -> Cons(1, stream_of_ones))

let rec primes_stream n (a: 'a my_lazy) = 
    let rec check x limit =
        if x > limit then 
            Cons(n, fix (primes_stream (n+1)))
        else
        (
            if n mod x = 0 then
                primes_stream(n+1) a
            else 
                check (x+1) limit
        )
    in if n < 2 then primes_stream 2 a else check 2 (n-1)

let primes = fix (primes_stream 2);;

module type OrderedType = 
sig 
    type t 
    val compare : t -> t -> int 
end;;

module OrderedList (X : OrderedType) : OrderedType with type t = X.t list = 
struct
    type t = X.t list
    (* xs < ys -> -1, xs = ys -> 0, xs > ys -> 1 *)
    let compare xs ys = 
        let rec foo xs ys =
            match xs, ys with
            | x1::xs1, y1::ys1 -> let res = X.compare x1 y1 in 
                if res = 0 then foo xs1 ys1 else res
            | [], y1::ys1 -> -1
            | x1::xs1, [] -> 1
            | [], [] -> 0
        in foo xs ys 
end;;

module OrderedPair (X : OrderedType) : OrderedType with type t = X.t * X.t = 
struct
    type t = X.t * X.t
    let compare (a1, a2) (b1, b2) = 
        let res1 = X.compare a1 b1 in
            if res1 <> 0 then res1 else X.compare a2 b2
end;;

module OrderedOption (X : OrderedType) : OrderedType with type t = X.t option = 
struct
    (* type t = None | Some of X.t *)
    type t = X.t option

    let compare o1 o2 = 
        match o1, o2 with
        | None, None -> 0
        | None, Some x -> -1
        | Some x, None -> 1
        | Some x, Some y -> X.compare x y
end;;
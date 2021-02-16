module Make(Key : OrderedType) : S with type key = Key.t = 
struct
    module Perm_map = Map.Make(Key)
    type key = Key.t
    type t = (key Perm_map.t) * (key Perm_map.t) 
    (* type t = Perm_map.t * Perm_map.t *)
    (** permutacja jako funkcja *)
    let apply (p, rev) k = 
        if Perm_map.mem k p then Perm_map.find k p else k
    (** permutacja identycznościowa *)
    let id = (Perm_map.empty, Perm_map.empty)
    (** permutacja odwrotna *)
    let invert (p, rev) = (rev, p)
    (** permutacja która tylko zamienia dwa elementy miejscami *)
    let swap k1 k2 = let emp = Perm_map.empty
        in let p_new = Perm_map.add k2 k1 (Perm_map.add k1 k2 emp)
            in (p_new, p_new)
    (** złożenie permutacji (jako złożenie funkcji) *)
    let compose (p2, rev2) (p1, rev1) = 
        let temp_map = Perm_map.merge (fun k xo yo -> match xo,yo with
        | Some x, _ -> Some (apply (p2, rev2) x)
        | _ -> None
        ) p1 p2 
        and 
        temp_rev_map = Perm_map.merge (fun k xo yo -> match xo,yo with
        | Some x, _ -> Some (apply (rev1, p1) x)
        | _ -> None
        ) rev2 rev1 
        in
            let p_new = Perm_map.merge (fun k xo yo -> match xo,yo with
            | Some x, _ -> Some x
            | None, Some y -> Some y
            | _ -> None
            ) temp_map p2 
            and
            rev_new = Perm_map.merge (fun k xo yo -> match xo,yo with
            | Some x, _ -> Some x
            | None, Some y -> Some y
            | _ -> None
            ) temp_rev_map rev1 
            in ((Perm_map.filter (fun k x -> (Key.compare k x) <> 0) p_new), (Perm_map.filter (fun k x -> (Key.compare k x) <> 0) rev_new))
    (** porównywanie permutacji *)
    let compare (p2, inv2) (p1, inv1) = Perm_map.compare Key.compare p2 p1
end;;
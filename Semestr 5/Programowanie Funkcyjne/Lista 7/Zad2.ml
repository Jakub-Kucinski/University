module type OrderedType = 
sig 
    type t 
    val compare : t -> t -> int 
end;;

module type S = 
sig 
    type key 
    type t
    (** permutacja jako funkcja *)
    val apply   : t -> key -> key
    (** permutacja identycznościowa *)
    val id      : t
    (** permutacja odwrotna *)
    val invert  : t -> t
    (** permutacja która tylko zamienia dwa elementy miejscami *)
    val swap    : key -> key -> t
    (** złożenie permutacji (jako złożenie funkcji) *)
    val compose : t -> t -> t
    (** porównywanie permutacji *)
    val compare : t -> t -> int
end;;

(* 
module Integers : OrderedType = 
struct
    type t = int
    let compare x y = x - y
end;; *)

module Make(Key : OrderedType) : S with type key = Key.t = 
struct
    module Perm_map = Map.Make(Key)
    type key = Key.t
    type t = (key Perm_map.t) * (key Perm_map.t) 
    (** permutacja jako funkcja *)
    let apply (p, rev) k = 
        if Perm_map.mem k p then Perm_map.find k p else k
    (** permutacja identycznościowa *)
    let id = (Perm_map.empty, Perm_map.empty)
    (** permutacja odwrotna *)
    let invert (p, rev) = (rev, p)
    (** permutacja która tylko zamienia dwa elementy miejscami *)
    let swap k1 k2 = if Perm.compare k1 k2 = 0 then id else let emp = Perm_map.empty
        in let p_new = Perm_map.add k2 k1 (Perm_map.add k1 k2 emp)
            in (p_new, p_new)
    (** złożenie permutacji (jako złożenie funkcji) *)
    let compose (p2, rev2) (p1, rev1) = 
        let temp_map = Perm_map.merge (fun k xo yo -> match xo,yo with
        | Some x, _ -> let temp = apply (p2, rev2) x in if Key.compare k temp = 0 then None else Some(temp)
        | _ -> None
        ) p1 p2 
        and 
        temp_rev_map = Perm_map.merge (fun k xo yo -> match xo,yo with
        | Some x, _ -> let temp = apply (rev1, p1) x in if Key.compare k temp = 0 then None else Some(temp)
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


module type S2 = 
sig
    type t
    val is_generated : t -> t list-> bool
end;;

module Make(Perm : S) : S2 with type t = Perm.t = 
struct
    module Perm_set = Set.Make(Perm : OrderedType)

    type t = Perm.t

    let is_generated p perms =  
        let x0 = Perm_set.add Perm.id (Perm_set.of_list perms)
        in let rec saturate_set dest xn = 
            if Perm_set.mem dest xn then true else
                let xn_inverted = Perm_set.map (fun sigma -> Perm.invert sigma) xn 
                in let rec add_compositions_of_one x ys s =
                        match ys with
                        | [] -> s 
                        | z::zs -> add_compositions_of_one x zs (Perm_set.add (Perm.compose x z) s)
                    and add_all_compositions xs ys s = 
                        match xs with
                        | [] -> s 
                        | z::zs -> add_all_compositions zs ys (add_compositions_of_one z ys s)
                    in let elems_of_set = Perm_set.elements xn
                        in let xn_composed = add_all_compositions elems_of_set elems_of_set Perm_set.empty
                            in let xn_plus_one = Perm_set.union xn_composed (Perm_set.union xn xn_inverted)
                                in if Perm_set.equal xn xn_plus_one then false else saturate_set dest xn_plus_one
            in saturate_set p x0 

end;;
type ('a, _) order1 =
    | Lt : ('a, 'b) order1
    | Eq : ('a, 'a) order1
    | Gt : ('a, 'b) order1

module type Type1 = sig
    type 'a t
end;;

module type OrderedType1 = sig
    include Type1
    val compare : 'a t -> 'b t -> ('a, 'b) order1
end;;

module type S = sig
    type 'a key
    type 'a value
    type t
    val empty  : t
    val add    : 'a key -> 'a value -> t -> t
    val remove : 'a key -> t -> t
    val find   : 'a key -> t -> 'a value
end;;


module Make(Key : OrderedType1)(Value : Type1) = struct
    type 'a key = 'a Key.t
    type 'a value = 'a Value.t

    type ex_key =
        | Key : 'a key -> ex_key
    type key_value_pair =
        | KeyVal : 'a key * 'a value -> key_value_pair

    module ExKey = struct
        type t = ex_key
        let compare (Key a) (Key b) =
            match (Key.compare a b) with
                |Lt -> -1
                |Eq -> 0
                |Gt -> 1
            
    end 
    module ExMap = Map.Make(ExKey)

    type t = key_value_pair ExMap.t

    let empty =
        ExMap.empty

    let add k v e =
        ExMap.add (Key k) (KeyVal (k,v)) e

    let remove k e =
        ExMap.remove (Key k) e

    let find (type a) (k : a key) e : a value =
        let KeyVal (fk, v) = ExMap.find (Key k) e
        in match (Key.compare k fk) with
                | Eq -> v
                | _  -> failwith "Impossible"
end;;
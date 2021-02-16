type 'a place = Place of 'a list * 'a list;;

let findNth list n = 
    let rec foo xs k acc = 
        match (k, xs) with
        | (0, _) -> Place(acc, xs)
        | (_, []) -> failwith("Value of n exceeded list length")
        | (k, h::t) -> foo t (k-1) (h::acc)
    in foo list n [];;

findNth [1; 2; 3; 4] 2;;

let collapse pl = 
    match pl with
    | Place (l1, l2) -> List.rev_append l1 l2;;

let add a pl = 
    match pl with
    | Place (l1, l2) -> Place(l1, a::l2);;

let del pl = 
    match pl with
    | Place (l1, []) -> failwith("Cannot delete value on given place")
    | Place (l1, h::t) -> Place(l1, t);;

collapse (add 5 (findNth [1; 2; 3; 4] 2)) = [1; 2; 5; 3; 4];;
collapse (del (findNth [1; 2; 3; 4] 2)) = [1; 2; 4];;

let next pl = 
    match pl with
    | Place (l1, []) -> failwith("Index out of range")
    | Place (l1, h::t) -> Place (h::l1, t);;

let prev pl = 
    match pl with
    | Place ([], l2) -> failwith("Index out of range")
    | Place (h::t, l2) -> Place (t, h::l2);;

let pl = findNth [1; 2; 3; 4] 2;;
next pl;;
prev pl;;

type dir = Left | Right
type 'a placet = ('a * 'a btree * dir) list * 'a btree ;;

let t1 = Node (Node (Leaf, 1, Leaf), 2, Node (Leaf, 3, Leaf))
let t2 = Node (Node (Leaf, 3, Leaf), 2, Node (Leaf, 1, Leaf))

([2, Node (Leaf, 3, Leaf), Left], Node (Leaf, 1, Leaf))
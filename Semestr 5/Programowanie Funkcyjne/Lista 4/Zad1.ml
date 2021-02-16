type 'a btree = Leaf | Node of 'a btree * 'a * 'a btree;;

let is_balanced tree =  
    let rec foo tr = 
    match tr with
    | Leaf -> (true, 0)
    | Node (lt, _, rt) -> let is_b_lt = foo lt 
                            and is_b_rt = foo rt
                          in if not (fst is_b_lt) || not (fst is_b_rt)
                                then (false, 0)
                                else if (snd is_b_lt) - (snd is_b_rt) >= -1
                                        && (snd is_b_lt) - (snd is_b_rt) <= 1
                                        then (true, (snd is_b_lt) + (snd is_b_rt) + 1)
                                        else (false, 0)
    in fst (foo tree);;

let tt_balanced = Node(Node(Node(Leaf, 4, Leaf), 2, Leaf), 1, Node(Node(Leaf, 5, Leaf), 3, Node(Leaf, 6, Leaf)));;

let tt_unbalanced = Node(Node(Node(Leaf, 4, Leaf), 2, Leaf), 1, Node(Node(Leaf, 5, Node(Leaf, 6, Leaf)), 3, Leaf));;

let build_balanced xs = 
    let rec foo n ys =
        match (n, ys) with
        | (0, _) -> (Leaf, ys)
        | (1, h::t) -> (Node(Leaf, h, Leaf), t)
        | (k, h::t) -> let (lt, zs) = foo ((k-1)/2) t
                        in let (rt, vs) = foo ((k-1) - ((k-1)/2)) zs
                            in (Node(lt, h, rt), vs)
    in fst (foo (List.length xs) xs);;

let xs = [1;2;3;4;5;6];;
type 'a dllist = 'a dllist_data lazy_t
    and 'a dllist_data = { 
        prev : 'a dllist; 
        elem : 'a; 
        next : 'a dllist};;

let prev (s: 'a dllist) = 
    match s with
    | lazy l -> l.prev;;

let next (s: 'a dllist) =
    match s with
    | lazy l -> l.next;;

let elem (s: 'a dllist) =
    match s with 
    | lazy l -> l.elem;;

let rec (lista1: 'a dllist) = lazy {prev = lista2; elem = 1; next = lista2}
    and (lista2: 'a dllist) = lazy {prev = lista1; elem = 2; next = lista1};;

next lista1 == lista2;;
next (next lista1) == lista1;;
next (prev lista1) == lista1;;

let of_list list = 
    match list with
    | [] -> failwith "Empty list"
    | x::[] -> let rec l = lazy {prev=l; elem=x; next=l} in l
    | x1::x2::xs -> let rec first = lazy {prev=snd(next_and_last_elems); elem=x1; next=fst(next_and_last_elems)}
                    and foo list previous =
                        match list with
                        | [] -> failwith "Empty list"
                        | x::[] -> let rec new_elem = lazy {prev=previous; elem=x; next=first}
                            in (new_elem, new_elem)
                        | x::xs -> let rec new_elem = lazy {prev=previous; elem=x; next=fst(subsequent_and_last_of_elems)} 
                            and subsequent_and_last_of_elems = foo xs new_elem
                            in (new_elem, snd(subsequent_and_last_of_elems))
                    and next_and_last_elems = foo (x2::xs) first 
                    in first;;


let of_list list = 
    let rec foo list previous first =
                        match list with
                        | [] -> failwith "Empty list"
                        | x::[] -> let rec new_elem = lazy {prev=previous; elem=x; next=first}
                            in (new_elem, new_elem)
                        | x::xs -> let rec new_elem = lazy {prev=previous; elem=x; next=fst(subsequent_and_last_of_elems)} 
                            and subsequent_and_last_of_elems = foo xs new_elem first
                            in (new_elem, snd(subsequent_and_last_of_elems))
    in match list with
    | [] -> failwith "Empty list"
    | x::[] -> let rec l = lazy {prev=l; elem=x; next=l} in l
    | x1::x2::xs -> let rec first = lazy {prev=snd(next_and_last_elems); elem=x1; next=fst(next_and_last_elems)}
                    and next_and_last_elems = foo (x2::xs) first first
                    in first;;




let of_list l = 
    let rec foo xs previous first = 
        match xs with
        | [] -> first
        | y::ys -> let rec current = lazy {prev = previous; elem = y; next = foo ys current first}
            in current
        and foo2 xs next first = 
        match xs with
        | [] -> first
        | y::ys ->
            let rec current = lazy {prev = foo2 ys current first; elem = y; next = next}
            in current
    in match l with 
    | [] -> failwith "Empty list"
    | x::xs -> let rec start = lazy {prev = foo2 (List.rev xs) start start; elem = x; next = foo xs start start}
        in start;;

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

let rec integers start_value = 
    let rec make_previous next n = 
        let rec current = lazy {prev=make_previous current (n - 1); elem=n; next=next}
        in current 
    in let rec make_next prev n=
        let rec current = lazy {prev=prev; elem=n; next=make_next current (n + 1)}
        in current 
    in
    let rec current = lazy {prev=make_previous current (start_value - 1); elem=n0; next= make_next current (start_value + 1)}
    in current;;
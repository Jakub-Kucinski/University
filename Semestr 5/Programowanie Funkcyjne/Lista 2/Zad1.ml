let rec add_head_to_all_sublists head lists acc = 
        match lists with
        y::ys -> (add_head_to_all_sublists head ys ((head::y)::acc))
        | [] -> acc;;

let rec sublists xs =
    match xs with
    y::ys -> let zs = sublists ys in add_head_to_all_sublists y zs zs
    | [] -> [[]];;


let l = [["Ala"; "ma"; "kota"]; ["Damiany"; "maja"; "psa"]; []];;

let test = [1;2;3];;

add_head_to_all_sublists "cos" l l;;

sublists test;;
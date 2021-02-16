let foo xs = 
    let rec foo2 ys acc = 
        match ys with
        | [] -> acc
        | z::zs -> foo2 zs (acc*10 + z)
    in foo2 xs 0;;

foo [3;7;8];;

let foo2 xs = List.fold_left (fun acc x -> acc*10 + x) 0 xs;;
foo2 [3;7;8];;

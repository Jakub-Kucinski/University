let polynomial xs x = 
    let rec foo2 ys acc = 
        match ys with
        | [] -> acc
        | z::zs -> foo2 zs (acc *. x +. z)
    in foo2 xs 0.;;

polynomial [1.;0.;-1.;2.] 2.;;

let polynomial_fold xs x = List.fold_left (fun acc z -> acc *. x +. z) 0. xs;;
polynomial_fold [1.;0.;-1.;2.] 2.;;
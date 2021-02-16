let rec polynomial_nieogonowa xs z =
    match xs with
    | [] -> 0.
    | y::ys -> y +. z *. (polynomial ys z);;

polynomial_nieogonowa [2.;-1.;0.;1.] 2.;;

let polynomial_right xs z = List.fold_right (fun x acc -> x +. acc *. z) xs 0.;;
polynomial_right [2.;-1.;0.;1.] 2.;;

let polynomial_ogonowa xs z =
    let rec foo ys acc power_of_z = 
        match ys with
        | [] -> acc
        | v::vs -> foo vs (acc +. power_of_z *. v) (power_of_z *. z)
    in foo xs 0. 1.;;

polynomial_ogonowa [2.;-1.;0.;1.] 2.;;

let polynomial_left xs z = fst (List.fold_left (fun (acc, pow) x -> (acc +. pow *. x, pow *. z)) (0., 1.) xs);;
polynomial_left [2.;-1.;0.;1.] 2.;;

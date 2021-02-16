let pred cn =
  let _, p = cn.cnum (function (a, _) -> (succ a, a)) (zero, zero)
  in 
    p
;;
(* (akt, pop) *)
let tail cl =
  let _, tl = cl.clist 
    (fun a (z1, _) -> (ccons a z1, z1))
  (cnil, cnil)
  in tl
;;

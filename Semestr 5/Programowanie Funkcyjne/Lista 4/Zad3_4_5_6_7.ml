type formula = Var of string | False | Imp of formula * formula;;

let rec string_of_formula f =
  match f with
  | False -> "_|_"
  | Var (str) -> str
  | Imp (f1, f2) -> match f1 with
    | Imp (_, _) -> "(" ^ (string_of_formula f1) ^ ") -> " ^ (string_of_formula f2)
    | _ -> (string_of_formula f1) ^ " -> " ^ (string_of_formula f2);;
  (* → ⊥ *)

let pp_print_formula fmtr f =
  Format.pp_print_string fmtr (string_of_formula f);;

type theorem = 
    Assum of formula 
    | Impi of formula list * formula * theorem 
    | Impe of formula list * formula * theorem * theorem 
    | Bote of formula list * formula * theorem;;

let assumptions thm =
  match thm with
  | Assum(f) -> [f]
  | Impi(fs, f, t) -> fs
  | Impe(fs, f, t1, t2) -> fs
  | Bote(fs, f, th) -> fs;;

let consequence thm =
  match thm with
  | Assum(f) -> f
  | Impi(fs, f, t) -> f
  | Impe(fs, f, t1, t2) -> f
  | Bote(fs, f, th) -> f;;

let pp_print_theorem fmtr thm =
  let open Format in
  pp_open_hvbox fmtr 2;
  begin match assumptions thm with
  | [] -> ()
  | f :: fs ->
    pp_print_formula fmtr f;
    fs |> List.iter (fun f ->
      pp_print_string fmtr ",";
      pp_print_space fmtr ();
      pp_print_formula fmtr f);
    pp_print_space fmtr ()
  end;
  pp_open_hbox fmtr ();
  pp_print_string fmtr "|-";
  pp_print_space fmtr ();
  pp_print_formula fmtr (consequence thm);
  pp_close_box fmtr ();
  pp_close_box fmtr ();;
(* ⊢ *)
(* type theorem = Assum of formula | Impi of formula list * formula * theorem | Impe of formula list * formula * theorem * theorem | Bote of formula list * formula * theorem;; *)

let by_assumption f = Assum(f);;

let imp_i f thm =
    let a = assumptions thm and phi = consequence thm
        in Impi(List.filter (fun x -> x <> f) a, Imp(f, phi), thm);;
  (* failwith "not implemented";; *)

let imp_e th1 th2 =
    let a1 = assumptions th1 and a2 = assumptions th2 
    and f1 = consequence th1 and f2 = consequence th2
        in match f1 with
        | Imp(form1, form2) -> if f2 <> form1
                                then failwith("Thorem 2 formula does not match the thorem 1 antecedent of implication")
                                else Impe(List.append a1 a2, form2, th1, th2)
        | _ -> failwith("Thorem 1 does not match the imp_e rule");;
  (* failwith "not implemented";; *)

let bot_e f thm =
    let a = assumptions thm 
        in Bote(a, f, thm);;
  (* failwith "not implemented";; *)

#install_printer pp_print_formula;;
#install_printer pp_print_theorem;;
let f = Imp(Imp(False, Var("q")), Var("p"));;
let g = Imp(Imp(False, Var("q")), Var("p"));;
let g_list = [g];;
List.filter (fun x -> x <> f) g_list;;

let th1 = imp_i (Var("p")) (by_assumption (Var("p")));;

let th2 = imp_i (Var("p")) (imp_i (Var("q")) (by_assumption (Var("p"))));;

let form_pqr = Imp(Var("p"), Imp(Var("q"), Var("r")));;
let form_pq = Imp(Var("p"), Var("q"));;
let thm_qr = imp_e (by_assumption form_pqr) (by_assumption (Var("p")));;
let thm_q = imp_e (by_assumption form_pq) (by_assumption (Var("p")));;
let th3 = imp_i form_pqr (imp_i form_pq (imp_i (Var("p")) (imp_e thm_qr thm_q)));;

let th4 = imp_i False (bot_e (Var("p")) (by_assumption False));;

(* let f = False;; *)

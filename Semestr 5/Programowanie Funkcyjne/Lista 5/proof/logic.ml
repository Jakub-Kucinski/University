type formula = Var of string | False | Imp of formula * formula

let rec string_of_formula f =
  match f with
  | False -> "⊥"
  | Var (str) -> str
  | Imp (f1, f2) -> match f1 with
    | Imp (_, _) -> "(" ^ (string_of_formula f1) ^ ") → " ^ (string_of_formula f2)
    | _ -> (string_of_formula f1) ^ " -> " ^ (string_of_formula f2)

let pp_print_formula fmtr f =
  Format.pp_print_string fmtr (string_of_formula f)

type theorem = 
    Assum of formula 
    | Impi of formula list * formula * theorem 
    | Impe of formula list * formula * theorem * theorem 
    | Bote of formula list * formula * theorem

let assumptions thm =
  match thm with
  | Assum(f) -> [f]
  | Impi(fs, f, t) -> fs
  | Impe(fs, f, t1, t2) -> fs
  | Bote(fs, f, th) -> fs

let consequence thm =
  match thm with
  | Assum(f) -> f
  | Impi(fs, f, t) -> f
  | Impe(fs, f, t1, t2) -> f
  | Bote(fs, f, th) -> f

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
  pp_print_string fmtr "⊢";
  pp_print_space fmtr ();
  pp_print_formula fmtr (consequence thm);
  pp_close_box fmtr ();
  pp_close_box fmtr ()


let by_assumption f = Assum(f)

let imp_i f thm =
    let a = assumptions thm and phi = consequence thm
        in Impi(List.filter (fun x -> x <> f) a, Imp(f, phi), thm)

let imp_e th1 th2 =
    let a1 = assumptions th1 and a2 = assumptions th2 
    and f1 = consequence th1 and f2 = consequence th2
        in match f1 with
        | Imp(form1, form2) -> if f2 <> form1
                                then failwith("Thorem 2 formula does not match the thorem 1 antecedent of implication")
                                else Impe(List.append a1 a2, form2, th1, th2)
        | _ -> failwith("Thorem 1 does not match the imp_e rule")

let bot_e f thm =
    let a = assumptions thm 
        in Bote(a, f, thm)



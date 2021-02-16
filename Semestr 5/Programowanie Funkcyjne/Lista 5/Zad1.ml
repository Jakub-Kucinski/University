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







type context = (string * formula) list;;
type goalDesc = context * formula;;

type proof = 
    | PImpi of formula list * formula * int * proof
    | PImpe of formula list * formula * int * proof * proof
    | PBote of formula list * formula * int * proof
    | PGoal of goalDesc
    | Theorem of theorem;;

type path = Root | Node of formula list * formula * int * proof list * path * bool;;
type goal = Goal of goalDesc * path;;

let qed pf =
  match pf with
  | Theorem(th) -> th
  | _ ->  failwith "expected complited theorem but got something else";;

let numGoals pf =
    match pf with
    | PImpi(_, _, n, _) -> n
    | PImpe(_, _, n, _, _) -> n
    | PBote(_, _, n, _) -> n
    | PGoal(_) -> 1
    | Theorem(_) -> 0;;

let rec goals pf =
    match pf with
    | PImpi(_, _, _, p) -> goals p
    | PImpe(_, _, _, p1, p2) -> (goals p1) @ (goals p2)
    | PBote(_, _, _, p) -> goals p
    | PGoal(g) -> [g]
    | Theorem(_) -> [];;

let proof g f =
    PGoal((g, f):goalDesc);;

let goal pf =
  match pf with 
  | Goal(gdsc, p) -> gdsc
  | _ -> failwith "expected goal but got something else";;

let focus n pf =
  let rec foo n pf path = 
    match pf with
    | PImpi(fl, f, k, p) -> if k < n then failwith "n greater then number of goals" else
                              foo n p (Node(fl, f, k, [], path, true))
    | PImpe(fl, f, k, pl, pr) -> 
    | PBote(fl, f, k, p) -> if k < n then failwith "n greater then number of goals" else
                              foo n p (Node(fl, f, k, [], path, true))
    | PGoal(gdsc) -> 1
    | Theorem(thm) -> 0;; 

let unfocus gl =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let next gl =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let prev gl =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let intro name gl =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let apply f gl =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let apply_thm thm gl =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let apply_assm name gl =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let pp_print_proof fmtr pf =
  let ngoals = numGoals pf
  and goals = goals pf
  in if ngoals = 0
  then Format.pp_print_string fmtr "No more subgoals"
  else begin
      Format.pp_open_vbox fmtr (-100);
      Format.pp_open_hbox fmtr ();
      Format.pp_print_string fmtr "There are";
      Format.pp_print_space fmtr ();
      Format.pp_print_int fmtr ngoals;
      Format.pp_print_space fmtr ();
      Format.pp_print_string fmtr "subgoals:";
      Format.pp_close_box fmtr ();
      Format.pp_print_cut fmtr ();
      goals |> List.iteri (fun n (_, f) ->
       Format.pp_print_cut fmtr ();
       Format.pp_open_hbox fmtr ();
       Format.pp_print_int fmtr (n + 1);
       Format.pp_print_string fmtr ":";
       Format.pp_print_space fmtr ();
       pp_print_formula fmtr f;
       Format.pp_close_box fmtr ());
      Format.pp_close_box fmtr ()
    end

let pp_print_goal fmtr gl =
  let (g, f) = goal gl
  in
  Format.pp_open_vbox fmtr (-100);
  g |> List.iter (fun (name, f) ->
      Format.pp_print_cut fmtr ();
      Format.pp_open_hbox fmtr ();
      Format.pp_print_string fmtr name;
      Format.pp_print_string fmtr ":";
      Format.pp_print_space fmtr ();
      pp_print_formula fmtr f;
      Format.pp_close_box fmtr ());
  Format.pp_print_cut fmtr ();
  Format.pp_print_string fmtr (String.make 40 '=');
  Format.pp_print_cut fmtr ();
  pp_print_formula fmtr f;
  Format.pp_close_box fmtr ()

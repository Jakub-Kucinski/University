module QBF where

type Var = String
data Formula
    = Var Var             -- zmienne zdaniowe
    | Bot                 -- spójnik fałszu(⊥)
    | Not Formula         -- negacja(¬φ)
    | And Formula Formula -- koniunkcja(φ∧ψ)
    | All Var     Formula -- kwantyfikacja uniwersalna(∀p.φ)



type Env = Var -> Bool
eval :: Env -> Formula -> Bool
eval env (Var var) = env var
eval env Bot = False 
eval env (Not form) = not (eval env form)
eval env (And form1 form2) = (eval env form1) && (eval env form2)
eval env (All var form) = (eval (\ v -> if v == var then True else env v) form) && (eval (\ v -> if v == var then False else env v) form)


isTrue :: Formula -> Bool
isTrue form = eval (\x -> False) form


-- f1 = All "p" (Var "p")
-- isTrue f1

-- f2 = All "p" (Not (All "q" (Not (And (Not (And (Var "p") (Var "q"))) (Not (And (Not (Var "p")) (Not (Var "q"))))))))
-- isTrue f2

module NestedQBF where
import Data.Void

data Formula v = Var v
    | Bot
    | Not (Formula v)
    | And (Formula v) (Formula v)
    | All (Formula (Inc v))

data Inc v = Z | S v

-- type Env = Inc v -> Bool

eval :: (v -> Bool) -> (Formula v)-> Bool
eval env (Var v) = env v
eval env Bot = False 
eval env (Not form) = not (eval env form)
eval env (And form1 form2) = (eval env form1) && (eval env form2)
eval env (All form) = (eval env1 form) && (eval env2 form) where
    env1 Z = True
    env1 (S v) = env v
    env2 Z = False
    env2 (S v) = env v


isTrue :: Formula Void -> Bool
isTrue form = eval absurd form
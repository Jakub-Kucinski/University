type Symbol = String
data Term v = Var v | Sym Symbol [Term v]

instance Functor Term where
    fmap f (Var v) = Var (f v) 
    fmap f (Sym s ls) = Sym s (map (fmap f) ls)

instance Applicative Term where
    pure a = Var a 
    (Var f) <*> t = fmap f t
    (Sym s ls) <*> t = Sym s (map (\x -> x <*> t) ls)

instance Monad Term where
    return = pure
    (Var x) >>= f = f x 
    (Sym s ls) >>= f = Sym s (map (\x -> x >>= f) ls)

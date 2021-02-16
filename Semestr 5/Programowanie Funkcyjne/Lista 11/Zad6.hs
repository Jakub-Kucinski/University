data Inc v = Z | S v
data Formula v 
    = Var v 
    | Bot 
    | Not (Formula v) 
    | And (Formula v) (Formula v) 
    | All (Formula (Inc v))

instance Functor Inc where
    fmap f Z = Z
    fmap f (S x) = S (f x)

instance Functor Formula where
    fmap f (Var v) = Var (f v)
    fmap f Bot = Bot
    fmap f (Not form) = Not (fmap f form)
    fmap f (And form1 form2) = And (fmap f form1) (fmap f form2)
    fmap f (All form) = All (fmap (foo f) form) where
        foo f Z = Z
        foo f (S x) = S (f x)

instance Applicative Inc where
    pure _ = Z
    fmap f (S x) = S (f x)

instance Applicative Formula where
    pure a = Var a
    (Var f) <*> t = fmap f t
    Bot <*> _ = Bot
    (Not f) <*> t = Not (fmap f t)

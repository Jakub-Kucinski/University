import Data.Void

data Formula v = 
    Var v
    | Bot
    | Not (Formula v)
    | And (Formula v) (Formula v)
    | All (Formula (Inc v))

data Inc v = Z | S v

-- Wprowadziłem nazwy Functorx i fmapx bo kompilator kłócił się, że nazwy Functor i fmap pochodzą z innych modułów
class Functorx t where
    fmapx :: (a -> b) -> t a -> t b

instance Functorx Inc where
    fmapx f Z = Z
    fmapx f (S x) = S (f x)

instance Functorx Formula where
    fmapx f (Var v) = Var (f v)
    fmapx f Bot = Bot
    fmapx f (Not form) = Not (fmapx f form)
    fmapx f (And form1 form2) = And (fmapx f form1) (fmapx f form2)
    fmapx f (All form) = All (fmapx (foo f) form) where
        foo f Z = Z
        foo f (S x) = S (f x)


substitute :: (a -> Formula b) -> Formula a -> Formula b
substitute f Bot = Bot
substitute f (Var v) = f v
substitute f (Not form) = Not (substitute f form)
substitute f (And form1 form2) = And (substitute f form1) (substitute f form2)
substitute f (All form) = All (substitute foo form) where 
    foo (S v) = fmapx S (f v)
    foo Z = Var Z


isTrue :: Formula Void -> Bool
isTrue (Var x) = absurd x
isTrue Bot = False
isTrue (Not form) = not (isTrue form)
isTrue (And form1 form2) = (isTrue form1) && (isTrue form2)
-- Jako true można podstawić not bot
isTrue (All form) = (isTrue (substitute (\x -> Bot) form)) && (isTrue (substitute (\x -> (Not Bot)) form))
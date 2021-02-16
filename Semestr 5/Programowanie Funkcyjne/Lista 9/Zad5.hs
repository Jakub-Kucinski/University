{-# LANGUAGE ScopedTypeVariables #-}

class Finite a where
    elems :: [a]
    index :: a -> Integer

instance Finite Bool where
    elems = [True, False]
    index a = if a then 0 else 1

instance Finite a => Finite (Maybe a) where
    elems = Nothing : (map (\x -> Just x) (elems::[a]))
    index (Just x) = 1 + index x
    index Nothing = 0

instance (Finite a, Finite b) => Finite (a, b) where
    elems = [(x,y) | x <- (elems ::[a]), y <- (elems ::[b])]
    index (x, y) = (index x) * (toInteger (length (elems :: [b]))) + (index y)

instance (Finite a, Finite b) => Finite (a -> b) where
    elems = map (\vals -> make_fun_from_lists (elems::[a]) vals) (make_values (length (elems::[a])) (elems::[b])) where 
        make_values 0 _ = [[]]
        make_values n list = [x:xs | x <- list, xs <- (make_values (n-1) list)]
        make_fun_from_lists (a:args) (v:vals) x = if index a == index x then v else make_fun_from_lists args vals x

    index f = let len_b = toInteger( length (elems :: [a])) in 
        foldl (\ acc x -> acc * len_b + (index (f x))) (toInteger 0) (elems :: [a])


-- 0
-- :{
--     test :: Bool -> Bool
--     test True = True
--     test False = True
-- :}
-- 1
-- :{
--     test :: Bool -> Bool
--     test True = True
--     test False = False
-- :}
-- 2
-- :{
--     test :: Bool -> Bool
--     test True = False
--     test False = True
-- :}
-- 3
-- :{
--     test :: Bool -> Bool
--     test True = False
--     test False = False
-- :}
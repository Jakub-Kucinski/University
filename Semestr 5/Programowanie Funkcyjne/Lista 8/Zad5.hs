qsortBy :: (a -> a -> Bool) -> [a] -> [a]
qsortBy f [] = []
qsortBy f (x:xs) = smaller ++ x : greater_eq
    where 
        smaller = qsortBy f [e | e <- xs, f e x]
        greater_eq = qsortBy f [e | e <- xs, not (f e x)]
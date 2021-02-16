cantor :: [a] -> [b] -> [b] -> [(a, b)]
cantor [] reversed_ys_on_diagonal [] = []
cantor (x:xs) reversed_ys_on_diagonal [] = zip xs reversed_ys_on_diagonal ++ cantor xs reversed_ys_on_diagonal []
cantor xs reversed_ys_on_diagonal (y:ys) = let new_ys_diag = y : reversed_ys_on_diagonal in 
                                                zip xs new_ys_diag ++ cantor xs new_ys_diag ys

(><) :: [a] -> [b] -> [(a, b)]
(><) xs ys = cantor xs [] ys
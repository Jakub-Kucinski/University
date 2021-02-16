inserteverywhere :: a -> [a] -> [a] -> [[a]]
inserteverywhere x left [] = [left++[x]]
inserteverywhere x left (r:right) = (left++(x:r:right)) : (inserteverywhere x (left++[r]) right)

permi :: [a] -> [[a]]
permi [] = [[]]
permi (x:xs) = concat (map (inserteverywhere x []) (permi xs))


perm_help [] xs_not_added = foldr (\ x list -> [x]:list) [] xs_not_added

import Data.List
perms :: Eq a => [a] -> [[a]]
perms [] = [[]]
perms [x] = [[x]]
perms xs = concat (map (\x -> map (\ list -> x:list) (perms (delete x xs))) xs)

-- perms xs = foldr (\ (y, ys) results -> ) [] (foldr (\x results -> (x,(delete x xs)):results) [] xs)
-- perms xs = foldr (\x results -> perms (delete x xs) : results) [] xs


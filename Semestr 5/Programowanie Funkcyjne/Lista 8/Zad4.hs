let sublist list = if list == [] then [[]]
    else (map (\ l -> (head list) : l) xs) ++ xs
        where xs = sublist (tail list)

sublist :: [a] -> [[a]]
sublist [] = [[]]
sublist (h:t) = (map (\ l -> h : l) xs) ++ xs where xs = sublist t
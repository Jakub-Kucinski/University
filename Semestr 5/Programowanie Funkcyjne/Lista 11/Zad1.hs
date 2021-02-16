class Monad m => Random m where
  random :: m Int

shuffle :: Random m => [a] -> m [a]
shuffle ls = shuffle_iter [] ls


shuffle_iter :: Random m => [a] -> [a] -> m [a]
shuffle_iter shufled [] = return (reverse shufled)
shuffle_iter shufled to_shuffle = random >>= \k -> let (elem, to_shuffle_without_elem) = pick k 0 [] to_shuffle in
    shuffle_iter (elem:shufled) to_shuffle_without_elem

pick :: Int -> Int -> [a] -> [a] -> (a, [a])
-- Przeszliśmy całą listę
pick k current_idx prior_elems [] = pick (k `mod` current_idx) 0 [] (reverse prior_elems)
-- wpp
pick k current_idx prior_elems (elem:ls) = if current_idx == k
                                           then (elem, (reverse prior_elems)++ls)
                                           else pick k (current_idx+1) (elem:prior_elems) ls
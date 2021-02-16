import Control.Applicative
data RegExp a
    = Eps
    | Lit  (a -> Bool)
    | Or   (RegExp a) (RegExp a)
    | Cat  (RegExp a) (RegExp a)
    | Star (RegExp a)

get_splits :: [a] -> [([a], [a])]
get_splits [a] = [([], [a]), ([a], [])]
get_splits (l:ls) = let minor_splits = (get_splits ls) in
    ([], l:ls) : (map (\x -> ((l:(fst x)), (snd x))) minor_splits)

check_split_cat :: MonadPlus m => RegExp a -> RegExp a -> [a] -> [([a], [a])] -> m (Maybe [a])
check_split_cat r1 r2 [] = return Nothing
check_split_cat r1 r2 (s:splits) = let (pre, suf) = s in do
    w1 <- match r1 pre
    case w1 of 
        Nothing -> check_split_cat r1 r2 splits
        (Just x1) -> do
            w2 <- match r2 suf
            case w2 of 
                Nothing -> check_split_cat r1 r2 splits
                (Just x2) -> return w1


match :: MonadPlus m => RegExp a -> [a] -> m (Maybe [a])
match Eps [] = return (Just [])
match Eps _ = return Nothing
match (Lit p) [a] = if p a
    then return (Just as)
    else return Nothing
match (Lit _) _ = return Nothing
match (Or r1 r2) as = do
    w1 <- match r1 as
    w2 <- match r2 as
    return (w1 <|> w2)
match (Cat r1 r2) as = let splits = get_splits as in 
    check_split_cat r1 r2 splits
    -- suf <- match r1 as
    -- case suf of
    --     Nothing -> return Nothing
    --     (Just suf) -> match r2 suf
match (Star r) as = do
    let l = length as
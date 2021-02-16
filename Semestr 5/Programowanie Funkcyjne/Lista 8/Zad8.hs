data Color = Red | Black
                deriving (Eq,Show,Read)
data RBTree a = RBNode Color (RBTree a) a (RBTree a) | RBLeaf
                deriving (Eq,Show,Read)

rotateLeft :: Ord a => RBTree a -> RBTree a
rotateLeft (RBNode c1 a x (RBNode c2 b y c)) = (RBNode c2 (RBNode c1 a x b) y c)

rotateRight :: Ord a => RBTree a -> RBTree a
rotateRight (RBNode c2 (RBNode c1 a x b) y c) = (RBNode c1 a x (RBNode c2 b y c))

makeRBNode :: Ord a => Color -> RBTree a -> a -> RBTree a -> RBTree a
makeRBNode Black (RBNode Red bl b (RBNode Red xl x xr)) a (RBNode Red cl c cr) = RBNode Red (RBNode Black bl b (RBNode Red xl x xr)) a (RBNode Black cl c cr)
-- makeRBNode Black (RBNode Red bl b (RBNode Red xl x xr)) a (RBNode Black cl c cr) = makeRBNode Black (rotateLeft (RBNode Red bl b (RBNode Red xl x xr))) a (RBNode Black cl c cr)
makeRBNode Black (RBNode Red bl b (RBNode Red xl x xr)) a (RBNode Black cl c cr) = RBNode Black (RBNode Red bl b xl) x (RBNode Red xr a (RBNode Black cl c cr))
makeRBNode Black (RBNode Red (RBNode Red xl x xr) b br) a (RBNode Black cl c cr) = RBNode Black (RBNode Red xl x xr) b (RBNode Red br a (RBNode Black cl c cr))

makeRBNode Black (RBNode Red bl b br) a (RBNode Red (RBNode Red xl x xr) c cr) = RBNode Red (RBNode Black bl b br) a (RBNode Black (RBNode Red xl x xr) c cr)
-- makeRBNode Black (RBNode Black bl b br) a (RBNode Red (RBNode Red xl x xr) c cr) = makeRBNode Black (RBNode Black bl b br) a (rotateRight (RBNode Red (RBNode Red xl x xr) c cr))
makeRBNode Black (RBNode Black bl b br) a (RBNode Red (RBNode Red xl x xr) c cr) = RBNode Black (RBNode Red (RBNode Black bl b br) a xl) x (RBNode Red xr c cr)
makeRBNode Black (RBNode Black bl b br) a (RBNode Red cl c (RBNode Red xl x xr)) = RBNode Black (RBNode Red (RBNode Black bl b br) a cl) c (RBNode Red xl x xr)

makeRBNode Black (RBNode Red (RBNode Red a x b) y c) z RBLeaf = RBNode Red (RBNode Black a x b) y (RBNode Black c z RBLeaf)
makeRBNode Black (RBNode Red a x (RBNode Red b y c)) z RBLeaf = RBNode Red (RBNode Black a x b) y (RBNode Black c z RBLeaf)
makeRBNode Black RBLeaf x (RBNode Red b y (RBNode Red c z d)) = RBNode Red (RBNode Black RBLeaf x b) y (RBNode Black c z d)
makeRBNode Black RBLeaf x (RBNode Red (RBNode Red b y c) z d) = RBNode Red (RBNode Black RBLeaf x b) y (RBNode Black c z d)
makeRBNode c t1 x t2 = RBNode c t1 x t2

-- makeRBNode :: Ord a => Color -> RBTree a -> a -> RBTree a -> RBTree a
-- makeRBNode Black (RBNode Red (RBNode Red a x b) y c) z d = RBNode Red (RBNode Black a x b) y (RBNode Black c z d)
-- makeRBNode Black (RBNode Red a x (RBNode Red b y c)) z d = RBNode Red (RBNode Black a x b) y (RBNode Black c z d)
-- makeRBNode Black a x (RBNode Red b y (RBNode Red c z d)) = RBNode Red (RBNode Black a x b) y (RBNode Black c z d)
-- makeRBNode Black a x (RBNode Red (RBNode Red b y c) z d) = RBNode Red (RBNode Black a x b) y (RBNode Black c z d)
-- makeRBNode c t1 x t2 = RBNode c t1 x t2

rbtreeInsertElem :: Ord a => a -> RBTree a -> RBTree a
rbtreeInsertElem x RBLeaf = makeRBNode Black RBLeaf x RBLeaf
rbtreeInsertElem x (RBNode c lt y rt) = 
    colorRoot (foo x (RBNode c lt y rt))
    where
        foo x RBLeaf = makeRBNode Red RBLeaf x RBLeaf
        foo x (RBNode c lt y rt)
            | x == y = (makeRBNode c lt y rt)
            | x < y = makeRBNode c (foo x lt) y rt 
            | x > y = makeRBNode c lt y (foo x rt)
        colorRoot (RBNode c lt y rt) = (RBNode Black lt y rt)


rbtreeFromList :: Ord a => [a] -> RBTree a
rbtreeFromList list = foldr rbtreeInsertElem RBLeaf list

rbtreeMember :: Ord a => a -> RBTree a -> Bool
rbtreeMember x RBLeaf = False
rbtreeMember x (RBNode c lt y rt) = if x == y then True else if x < y then rbtreeMember x lt else rbtreeMember x rt

rbtreeListFromTree :: Ord a => RBTree a -> [a]
rbtreeListFromTree RBLeaf = []
rbtreeListFromTree (RBNode c lt x rt) = preorder (RBNode c lt x rt) []
    where
        preorder RBLeaf acc = acc
        preorder (RBNode c lt x rt) acc = preorder rt (preorder lt (x:acc))

rbtreeUnion :: Ord a => RBTree a -> RBTree a -> RBTree a
rbtreeUnion t1 t2 = foldr rbtreeInsertElem t2 (rbtreeListFromTree t1)

rbtreeIntersection :: Ord a => RBTree a -> RBTree a -> RBTree a
rbtreeIntersection t1 t2 = foldr rbtreeInsertElem RBLeaf (filter (\ x -> rbtreeMember x t2) (rbtreeListFromTree t1))

rbtreeDiff :: Ord a => RBTree a -> RBTree a -> RBTree a
rbtreeDiff t1 t2 = foldr rbtreeInsertElem RBLeaf (filter (\ x -> not (rbtreeMember x t2)) (rbtreeListFromTree t1))



data Set a = Fin (RBTree a) | Cofin (RBTree a)
                deriving (Eq,Show,Read)

setFromList :: Ord a => [a] -> Set a
setFromList list = Fin (rbtreeFromList list)

setEmpty :: Ord a => Set a
setEmpty = Fin RBLeaf

setFull :: Ord a => Set a
setFull = Cofin RBLeaf

setUnion :: Ord a => Set a -> Set a -> Set a
setUnion (Fin t1) (Fin t2) = Fin (rbtreeUnion t1 t2)
setUnion (Cofin t1) (Cofin t2) = Cofin (rbtreeIntersection t1 t2)
setUnion (Cofin t1) (Fin t2) = Cofin (rbtreeDiff t1 t2)
setUnion (Fin t1) (Cofin t2) = Cofin (rbtreeDiff t2 t1)

setIntersection :: Ord a => Set a -> Set a -> Set a
setIntersection (Fin t1) (Fin t2) = Fin (rbtreeIntersection t1 t2)
setIntersection (Cofin t1) (Cofin t2) = Cofin (rbtreeUnion t1 t2)
setIntersection (Cofin t1) (Fin t2) = Fin (rbtreeDiff t2 t1)
setIntersection (Fin t1) (Cofin t2) = Fin (rbtreeDiff t1 t2)

setComplement :: Ord a => Set a -> Set a
setComplement (Fin t) = Cofin t 
setComplement (Cofin t) = Fin t

setMember :: Ord a => a -> Set a -> Bool
setMember x (Fin t) = rbtreeMember x t 
setMember x (Cofin t) = not (rbtreeMember x t)
data Tree a = Node (Tree a) a (Tree a) | Leaf
                deriving (Eq,Show,Read)

treeInsertElem :: Ord a => a -> Tree a -> Tree a
treeInsertElem x Leaf = Node Leaf x Leaf
treeInsertElem x (Node lt y rt) = if x < y then Node (treeInsertElem x lt) y rt else if x == y then (Node lt y rt) else Node lt y (treeInsertElem x rt)

treeFromList :: Ord a => [a] -> Tree a
treeFromList list = foldr treeInsertElem Leaf list

treeMember :: Ord a => a -> Tree a -> Bool
treeMember x Leaf = False
treeMember x (Node lt y rt) = if x == y then True else if x < y then treeMember x lt else treeMember x rt

treeListFromTree :: Ord a => Tree a -> [a]
treeListFromTree Leaf = []
treeListFromTree (Node lt x rt) = preorder (Node lt x rt) []
    where
        preorder Leaf acc = acc
        preorder (Node lt x rt) acc = preorder rt (preorder lt (x:acc))

treeUnion :: Ord a => Tree a -> Tree a -> Tree a
treeUnion t1 t2 = foldr treeInsertElem t2 (treeListFromTree t1)

treeIntersection :: Ord a => Tree a -> Tree a -> Tree a
treeIntersection t1 t2 = foldr treeInsertElem Leaf (filter (\ x -> treeMember x t2) (treeListFromTree t1))

treeDiff :: Ord a => Tree a -> Tree a -> Tree a
treeDiff t1 t2 = foldr treeInsertElem Leaf (filter (\ x -> not (treeMember x t2)) (treeListFromTree t1))



data Set a = Fin (Tree a) | Cofin (Tree a)
                deriving (Eq,Show,Read)

setFromList :: Ord a => [a] -> Set a
setFromList list = Fin (treeFromList list)

setEmpty :: Ord a => Set a
setEmpty = Fin Leaf

setFull :: Ord a => Set a
setFull = Cofin Leaf

setUnion :: Ord a => Set a -> Set a -> Set a
setUnion (Fin t1) (Fin t2) = Fin (treeUnion t1 t2)
setUnion (Cofin t1) (Cofin t2) = Cofin (treeIntersection t1 t2)
setUnion (Cofin t1) (Fin t2) = Cofin (treeDiff t1 t2)
setUnion (Fin t1) (Cofin t2) = Cofin (treeDiff t2 t1)

setIntersection :: Ord a => Set a -> Set a -> Set a
setIntersection (Fin t1) (Fin t2) = Fin (treeIntersection t1 t2)
setIntersection (Cofin t1) (Cofin t2) = Cofin (treeUnion t1 t2)
setIntersection (Cofin t1) (Fin t2) = Fin (treeDiff t2 t1)
setIntersection (Fin t1) (Cofin t2) = Fin (treeDiff t1 t2)

setComplement :: Ord a => Set a -> Set a
setComplement (Fin t) = Cofin t 
setComplement (Cofin t) = Fin t

setMember :: Ord a => a -> Set a -> Bool
setMember x (Fin t) = treeMember x t 
setMember x (Cofin t) = not (treeMember x t)

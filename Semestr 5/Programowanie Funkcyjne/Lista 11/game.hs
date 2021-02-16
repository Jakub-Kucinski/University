{-# LANGUAGE FlexibleContexts, FlexibleInstances, FunctionalDependencies #-}
-- zadanie 3

class Monad m => TwoPlayerGame m s a b | m -> s a b where
  moveA :: s -> m a
  moveB :: s -> m b

data Score = AWins | Draw | BWins

type AMove = String
type BMove = String
data Move = X | O deriving ( Eq )
data Cell = Occupied Move | Empty deriving ( Eq )
type Board = [Cell]

emptyBoard :: Board
emptyBoard = [Empty, Empty, Empty,
              Empty, Empty, Empty,
              Empty, Empty, Empty]

getBoardIndex :: String -> Maybe Int
getBoardIndex "A1" = Just 0
getBoardIndex "A2" = Just 1
getBoardIndex "A3" = Just 2
getBoardIndex "B1" = Just 3
getBoardIndex "B2" = Just 4
getBoardIndex "B3" = Just 5
getBoardIndex "C1" = Just 6
getBoardIndex "C2" = Just 7
getBoardIndex "C3" = Just 8
getBoardIndex _    = Nothing

verifyIsFree :: Board -> Int -> Maybe Int
verifyIsFree board index = if (board !! index) == Empty
                              then (Just index)
                              else Nothing


data MoveResult = Success Board | Fail
makeMove :: String -> Move -> Board -> MoveResult
makeMove position move board =
  case getBoardIndex position >>= verifyIsFree board of
    Nothing -> Fail
    Just i -> Success ((take i board) ++ [Occupied move] ++ (drop (i+1) board))

data GameState = Over Score | Play Board

-- gracz A stawia X, gracz B stawia O
isGameOver :: Move -> MoveResult -> GameState
isGameOver X Fail = Over BWins
isGameOver O Fail = Over AWins
isGameOver move (Success board) =
  case (move, or [
    -- check top row
    board !! 0 == (Occupied move) && board !! 1 == (Occupied move) && board !! 2 == (Occupied move),
    -- check middle row
    board !! 3 == (Occupied move) && board !! 4 == (Occupied move) && board !! 5 == (Occupied move),
    -- check bottom row
    board !! 6 == (Occupied move) && board !! 7 == (Occupied move) && board !! 8 == (Occupied move),
    -- check left column
    board !! 0 == (Occupied move) && board !! 3 == (Occupied move) && board !! 6 == (Occupied move),
    -- check middle column
    board !! 1 == (Occupied move) && board !! 4 == (Occupied move) && board !! 7 == (Occupied move),
    -- check right column
    board !! 2 == (Occupied move) && board !! 5 == (Occupied move) && board !! 8 == (Occupied move),
    -- check top left -> bottom right
    board !! 0 == (Occupied move) && board !! 4 == (Occupied move) && board !! 8 == (Occupied move),
    -- check bottom left -> top right
    board !! 6 == (Occupied move) && board !! 4 == (Occupied move) && board !! 2 == (Occupied move)
  ]) of
    (X, True) -> Over AWins
    (O, True) -> Over BWins
    (_, False) -> if isFullBoard board
                     then Over Draw
                     else Play board

isFullBoard :: Board -> Bool
isFullBoard board = all (\x -> x /= Empty) board

playTicTacToeA :: TwoPlayerGame m Board AMove BMove => Board -> m Score
playTicTacToeA board = let ma = moveA board in ma >>= (\s -> let mr = makeMove s X board in
                                                         case isGameOver X mr of
                                                           Over state -> return state
                                                           Play b -> playTicTacToeB b)

playTicTacToeB :: TwoPlayerGame m Board AMove BMove => Board -> m Score
playTicTacToeB board = let mb = moveB board in mb >>= (\s -> let mr = makeMove s O board in
                                                         case isGameOver O mr of
                                                           Over state -> return state
                                                           Play b -> playTicTacToeA b)

game :: TwoPlayerGame m Board AMove BMove => m Score
game = playTicTacToeA emptyBoard

-- zadanie 4
instance Show Move where
  show X = "X"
  show O = "O"

instance Show Cell where
  show (Occupied X)     = "X"
  show (Occupied O)    = "O"
  show Empty            = " "

-- renderRow :: Board -> String
-- renderRow row = " " ++ (show $ row !! 0) ++ " | " ++ (show $ row !! 1) ++ " | " ++ (show $ row !! 2)

-- dividingLine :: String
-- dividingLine = "----------"

-- renderBoard :: Board -> IO ()
-- renderBoard board = do
--   putStrLn $ renderRow firstRow
--   putStrLn dividingLine
--   putStrLn $ renderRow secondRow
--   putStrLn dividingLine
--   putStrLn $ renderRow thirdRow
--   where firstRow  = take 3 board
--         secondRow = drop 3 . take 6 $ board
--         thirdRow  = drop 6 board

newtype IOGame s a b x = IOGame {runIOGame :: IO x}

instance (Show s, Read a, Read b) => TwoPlayerGame (IOGame s a b) s a b where
  moveA state = do
    IOGame (putStrLn $ show state)
    IOGame (putStrLn "\nMove:")
    cell <- IOGame(getLine)
    return (read cell)
  moveB state = do
    IOGame (putStrLn $ show state)
    IOGame (putStrLn "\nMove:")
    cell <- IOGame(getLine)
    return (read cell)

-- read :: (Read a) => String -> a


instance Functor (IOGame s a b) where
  fmap f (IOGame x) = IOGame (fmap f)

instance Applicative (IOGame s a b) where
  pure a = IOGame (pure a)
  (IOGame f) (<*>) (IOGame g) = IOGame (f <*> g)

instance Monad (IOGame s a b) where
  return = pure
  (IOGame x) >>= f = IOGame (x ==> (runIOGame . f))


-- runIOStream game
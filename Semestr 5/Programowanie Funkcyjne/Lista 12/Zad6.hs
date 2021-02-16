{-# LANGUAGE FlexibleContexts, FlexibleInstances, FunctionalDependencies #-}
import Control.Monad.State

class Monad m => BFMonad m a | m -> a where
    bfMTapeGet   :: m a
    bfMTapePut   :: a -> m ()
    bfMMoveLeft  :: m ()
    bfMMoveRight :: m ()
    bfMInput     :: m ()
    bfMOutput    :: m ()

data BF
    = MoveR
    | MoveL
    | Inc
    | Dec
    | Output
    | Input
    | While [BF]
    deriving (Eq)

coerceEnum :: (Enum a, Enum b) => a -> b
coerceEnum = toEnum . fromEnum

evalBF :: BFMonad m Integer => [BF] -> m ()
evalBF [] = return []
evalBF (b:bf) = do
    let command = case b of
        MoveR -> bfMMoveRight
        MoveL -> bfMMoveLeft
        Inc -> bfMTapeGet >>= (\x -> bfMTapePut (x+1))
        Dec -> bfMTapeGet >>= (\x -> bfMTapePut (x-1))
        Output -> bfMOutput
        Input -> bfMInput >>= bfMInput
        (While bfs) -> do
            current <- bfMTapeGet
            if current == 0
                then evalBF bf 
                else evalBF bfs >> evalBF (b:bf)
    command >> evalBF bf


type Tape = ([Integer], [Integer])

emptyTape :: Tape
emptyTape = ([0, 0..], [0, 0..])

type BFState = ([Char], Tape, [Char])

instance BFMonad (State BFState) Integer where
    -- bfMTapeGet   :: m a
    bfMTapeGet = do
        (_, tape, _) <- get 
        return (head (fst tape))
    -- bfMTapePut   :: a -> m ()
    bfMTapePut a = do 
        (i, (l:ls, r), o) <- get
        put (i, (a:ls, r), o)
    -- bfMMoveLeft  :: m ()
    bfMMoveLeft = do
        (i, (l:ls, r), o) <- get
        put (i, (ls, l:rs), o)
    -- bfMMoveRight :: m ()
    bfMMoveLeft = do
        (i, (ls, r:rs), o) <- get
        put (i, (r:ls, rs), o)
    -- bfMInput     :: m ()
    bfMInput = do
        (i:is, t, o) <- get
        put (is, t, o)
        return (coerceEnum i)
    -- bfMOutput    :: m ()
    bfMOutput = do
        (i, (l:ls, r), o) <- get
        put (i:is, (l:ls, r), ((coerceEnum x):o))


runBF :: [BF] -> [Char] -> [Char]
runBF bf i = let (_, _, o) = execState (evalBF bf) (i, emptyTape, []) in reverse o

-- runBF [Input, Output, Input, Output, Inc, Output] ['a', 'b']
-- "abc"

-- runBF [Inc, Inc, While [MoveL, Input, Inc, Output, MoveR, Dec]] "ab"

{-# LANGUAGE FlexibleContexts, FlexibleInstances, FunctionalDependencies #-}
import Control.Monad.State

data StreamTrans i o a = 
    Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

runIOStreamTrans :: StreamTrans Char Char a -> IO a
runIOStreamTrans (ReadS f) = do c <- getChar
                                if c /= '\4' 
                                    then runIOStreamTrans (f (Just c))
                                    else runIOStreamTrans (f Nothing)
runIOStreamTrans (WriteS o s) = do putChar o
                                   runIOStreamTrans s
runIOStreamTrans (Return a) = return a

listTrans :: StreamTrans i o a -> [i] -> ([o], a)
listTrans (ReadS f) (l:ls) = listTrans (f (Just l)) ls
listTrans (ReadS f) [] = listTrans (f Nothing) []
listTrans (WriteS o s) ls = (o:xs, a) where 
    (xs, a) = listTrans s ls
listTrans (Return a) ls = ([], a)


instance Functor (StreamTrans i o) where
    fmap f (Return a) = Return (f a)
    fmap f (WriteS o s) = WriteS o (fmap f s)
    fmap f (ReadS f2) = ReadS g where
        g x = fmap f (f2 x)

instance Applicative (StreamTrans i o) where
    pure = Return
    (<*>) (Return f) s = fmap f s 
    (<*>) (WriteS o s1) s2 = WriteS o (s1 <*> s2)
    (<*>) (ReadS f) s = ReadS g where
        g x = (f x) <*> s 

instance Monad (StreamTrans i o) where
    (>>=) (Return a) f = f a 
    (>>=) (ReadS f) f2 = (ReadS g) where
        g x = (f x) >>= f2
    (>>=) (WriteS o s) f = (WriteS o (s >>= f))

instance Show BF where
  show MoveR      = ">"
  show MoveL      = "<"
  show Inc        = "+"
  show Dec        = "-"
  show Output     = "."
  show Input      = ","
  show (While bf) = "[" ++ show bf ++ "]"

brainfuckParser :: StreamTrans Char BF ()
brainfuckParser = ReadS fun where
  fun Nothing = Return ()
  fun (Just '>') = write MoveR
  fun (Just '<') = write MoveL
  fun (Just '+') = write Inc
  fun (Just '-') = write Dec
  fun (Just '.') = write Output
  fun (Just ',') = write Input
  fun (Just '[') = catchOutput brainfuckParser >>= \(_, bf) -> write (While bf)
  fun (Just ']') = Return ()
  fun (Just  _ ) = brainfuckParser
  write o = WriteS o brainfuckParser


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

class Monad m => TapeMonad m a | m -> a where
    tapeGet   :: m a
    tapePut   :: a -> m ()
    moveLeft  :: m ()
    moveRight :: m ()

evalBF_iter :: TapeMonad m Integer => [BF] -> [Char] -> m ([Char], [Char])
evalBF_iter [] _ = return ("", ls)
evalBF_iter (MoveR:bf) ls = do 
    moveRight
    evalBF_iter bf ls
evalBF_iter (MoveL:bf) ls = do 
    moveLeft
    evalBF_iter bf ls
evalBF_iter (Inc:bf) ls = do
    tapeGet >>= (\x -> tapePut (x+1))
    evalBF_iter bf ls
evalBF_iter (Dec:bf) ls = do
    tapeGet >>= (\x -> tapePut (x-1))
    evalBF_iter bf ls
evalBF_iter (Output:bf) ls = do 
    num <- tapeGet
    let c = coerceEnum num
    (res, xs) <- evalBF_iter bf ls
    return (c:res, xs)
evalBF_iter (Input:bf) (l:ls) = do
    tapePut (coerceEnum l)
    evalBF_iter bf ls
evalBF_iter ((While bfs):bf) ls = do
    current <- tapeGet
    if current == 0
        then evalBF_iter bf ls
        else do 
            (res, xs) <- evalBF_iter bfs ls
            (res2, ys) <- evalBF_iter ((While bfs):bf) xs
            return (res++res2, ys)

evalBF :: TapeMonad m Integer => [BF] -> [Char] -> m [Char]
evalBF bf ls = do
    (res, _) <- evalBF_iter bf ls
    return res



-- Zad4
type Tape = ([Integer], [Integer])

emptyTape :: Tape
emptyTape = ([0, 0..], [0, 0..])

instance TapeMonad (State Tape) Integer where
    -- tapeGet   :: m a
    tapeGet = do
        tape <- get 
        return (head (fst tape))
    -- tapePut   :: a -> m ()
    tapePut a = do 
        (l:ls, r) <- get
        put (a:ls, r)
    -- moveLeft  :: m ()
    moveLeft = do
        (l:ls, rs) <- get
        put (ls, l:rs)
    -- moveRight :: m ()
    moveRight = do
        (ls, r:rs) <- get
        put (r:ls, rs)

runBF :: [BF] -> [Char] -> [Char]
runBF bf ls = runState (evalBF bf ls) emptyTape

-- runBF [Input, Output, Input, Output, Inc, Output] ['a', 'b']
-- "abc"
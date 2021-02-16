import Data.Char
import Control.Monad

data StreamTrans i o a
        = Return a
        | ReadS (Maybe i -> StreamTrans i o a)
        | WriteS o (StreamTrans i o a)

toLower :: StreamTrans Char Char ()
toLower = ReadS f where
  f (Just i) = WriteS (Data.Char.toLower i) Main.toLower
  f Nothing = Return ()

nextChar :: StreamTrans Char Char ()
nextChar = ReadS f where
  f (Just i) = case i of
    'z' -> WriteS 'a' Main.nextChar
    'Z' -> WriteS 'A' Main.nextChar
    _ -> WriteS (succ i) Main.nextChar
  f Nothing = Return ()

runIOStreamTrans :: StreamTrans Char Char a -> IO a
runIOStreamTrans (ReadS f) = do c <- getChar
                                if c /= '\4'
                                  then runIOStreamTrans(f (Just c))
                                  else runIOStreamTrans(f Nothing)
runIOStreamTrans (WriteS output s) = do putChar output
                                        runIOStreamTrans s
runIOStreamTrans (Return a) = return a

catchOutput_iter :: StreamTrans i o a -> [o] -> StreamTrans i b (a, [o])
catchOutput_iter (Return a) ls = Return (a, reverse ls)
catchOutput_iter (WriteS o s) ls = catchOutput_iter s (o:ls)
catchOutput_iter (ReadS f) ls = ReadS g where
    g x = catchOutput_iter (f x) ls

catchOutput :: StreamTrans i o a -> StreamTrans i b (a, [o])
catchOutput s = catchOutput_iter s []

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

data BF
  = MoveR       -- >
  | MoveL       -- <
  | Inc         -- +
  | Dec         -- -
  | Output      -- .
  | Input       -- ,
  | While [BF]  -- [  ]
  deriving ( Eq )

brainfuckParser :: StreamTrans Char BF ()
brainfuckParser = ReadS f where
  f Nothing = Return ()
  f (Just '[') = catchOutput brainfuckParser >>= (\ (_, ls) -> WriteS (While ls) brainfuckParser)
  f (Just ']') = Return ()
  f (Just x) = WriteS y brainfuckParser where
    y = case x of
      '>' -> MoveR
      '<' -> MoveL
      '+' -> Inc
      '-' -> Dec
      '.' -> Output
      ',' -> Input

coerceEnum :: (Enum a, Enum b) => a -> b
coerceEnum = toEnum . fromEnum

type Tape = ([Integer], [Integer])

empty :: Tape
empty = ([0], [])

curr :: Tape -> Integer
curr (l, _) = head l

inc :: Tape -> Tape
inc (h:ls, rs) = ((h+1):ls,rs)

dec :: Tape -> Tape
dec (h:ls, rs) = ((h-1):ls,rs)

set :: Tape -> Integer -> Tape
set (h:ls, rs) x = (x:ls,rs)

moveRight :: Tape -> Tape
moveRight (ls, []) = (0:ls, [])
moveRight (ls, h:rs) = (h:ls, rs)

moveLeft :: Tape -> Tape
moveLeft (h:[], rs) = ([0], h:rs)
moveLeft (h:ls, rs) = (ls, h:rs)

evalBF :: Tape -> BF -> StreamTrans Char Char Tape
evalBF tape MoveR = Return (moveRight tape)
evalBF tape MoveL = Return (moveLeft tape)
evalBF tape Inc = Return (inc tape)
evalBF tape Dec = Return (dec tape)
evalBF tape Output = WriteS (coerceEnum (curr tape)) (Return tape)
evalBF tape Input = ReadS f where
  f (Just x) = Return (set tape (coerceEnum x))
evalBF tape (While bf) = if curr tape == 0
                            then Return tape
                            else (evalBFBlock tape bf >>= (\t -> evalBF t (While bf)))

evalBFBlock :: Tape -> [BF] -> StreamTrans Char Char Tape
evalBFBlock = Control.Monad.foldM evalBF

runBF :: [BF] -> StreamTrans Char Char ()
runBF bf = fmap (\_ -> ()) (evalBFBlock empty bf)

-- p = fst (listTrans brainfuckParser [])
-- runIOStreamTrans runBF p
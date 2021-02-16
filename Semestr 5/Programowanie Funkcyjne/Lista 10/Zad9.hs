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


data BF
  = MoveR       -- >
  | MoveL       -- <
  | Inc         -- +
  | Dec         -- -
  | Output      -- .
  | Input       -- ,
  | While [BF]  -- [  ]

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


import Data.Char

data StreamTrans i o a = 
    Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)


-- toLower :: StreamTrans Char Char a
toLower :: StreamTrans Char Char ()
toLower = ReadS f where
    f Nothing = Return ()
    f (Just x) = WriteS (Data.Char.toLower x) Main.toLower


runIOStreamTrans :: StreamTrans Char Char a -> IO a
runIOStreamTrans (ReadS f) = do c <- getChar
                                if c /= '\4' 
                                    then runIOStreamTrans (f (Just c))
                                    else runIOStreamTrans (f Nothing)
runIOStreamTrans (WriteS o s) = do putChar o
                                   runIOStreamTrans s
runIOStreamTrans (Return a) = return a


(|>|) :: StreamTrans i m a -> StreamTrans m o b -> StreamTrans i o b
(|>|) _ (Return b) = (Return b)
(|>|) (Return a)  (ReadS f) = (Return a) |>| (f Nothing)
(|>|) s1 (WriteS o s2) = (WriteS o (s1 |>| s2))
-- (Return a) |>| (WriteS o s)  = (WriteS o ((Return a) |>| s))
-- (ReadS f) |>| (WriteS o s) = (WriteS o ((ReadS f) |>| s))
-- (WriteS o1 s1) |>| (WriteS o2 s2) 
(|>|) (ReadS f1) (ReadS f2) = (ReadS s) where
    s x = (f1 x) |>| (ReadS f2)
(|>|) (WriteS o s) (ReadS f) = s |>| (f (Just o))

-- (|>|) :: StreamTrans i m a -> StreamTrans m o b -> StreamTrans i o b
-- (|>|) _ (Return b) = (Return b)
-- (|>|) (Return a) (ReadS f) = (Return a) |>| (f Nothing)
-- (|>|) firstStream (WriteS output s) = (WriteS output (firstStream |>| s))
-- (|>|) (ReadS f1) (ReadS f2) = (ReadS s)  where
--   s x = (f1 x) |>| (ReadS f2)
-- (|>|) (WriteS output s) (ReadS f) = s |>| (f (Just output))

nextChar :: StreamTrans Char Char ()
nextChar = ReadS f where
  f (Just i) = case i of
    'z' -> WriteS 'a' Main.nextChar
    'Z' -> WriteS 'A' Main.nextChar
    _ -> WriteS (succ i) Main.nextChar
  f Nothing = Return ()

-- runIOStreamTrans (Main.toLower |>| nextChar)
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
    (>>=) (ReadS f) f2 = ReadS g where
        g x = (f x) >>= f2
    (>>=) (WriteS o s) f = (WriteS o (s >>= f))

stream = (ReadS (\x -> Return (Data.Maybe.fromJust x))) >>= (\x -> WriteS x (Return ()))
runIOStreamTrans stream
import Data.Char

data StreamTrans i o a = 
    Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)


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

catchOutput_iter :: StreamTrans i o a -> [o] -> StreamTrans i b (a, [o])
catchOutput_iter (Return a) ls = Return (a, reverse ls)
catchOutput_iter (WriteS o s) ls = catchOutput_iter s (o:ls)
catchOutput_iter (ReadS f) ls = ReadS g where
    g x = catchOutput_iter (f x) ls

catchOutput :: StreamTrans i o a -> StreamTrans i b (a, [o])
catchOutput s = catchOutput_iter s []

runIOStreamTrans (catchOutput nextChar)
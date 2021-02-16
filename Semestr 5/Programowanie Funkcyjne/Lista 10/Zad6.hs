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

runCycle_iter :: StreamTrans a a b -> Maybe a -> b
runCycle_iter (Return b) _ = b
runCycle_iter (WriteS o s) _ = runCycle_iter s (Just o)
runCycle_iter (ReadS f) o = runCycle_iter (f o) Nothing

runCycle :: StreamTrans a a b -> b
runCycle s = runCycle_iter s Nothing
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


listTrans :: StreamTrans i o a -> [i] -> ([o], a)
listTrans (ReadS f) (l:ls) = listTrans (f (Just l)) ls
listTrans (ReadS f) [] = listTrans (f Nothing) []
listTrans (WriteS o s) ls = (o:xs, a) where 
    (xs, a) = listTrans s ls
listTrans (Return a) ls = ([], a)
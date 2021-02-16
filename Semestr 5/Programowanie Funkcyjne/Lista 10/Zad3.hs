import System.IO
import Data.Char

-- echoLower = do done <- isEOF
--             if done
--               then putStr ""
--               else do inp <- getLine
--                       putStrLn (map toLower inp)
--                       echoLower
echoLower :: IO ()
echoLower = do c <- getChar
               if c /= '\4' 
               then do putChar (toLower c)
                       echoLower
               else putStr ""
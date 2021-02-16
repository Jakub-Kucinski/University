sprintf :: ((a -> a) -> String -> t) -> t
sprintf k = k id ""

(^^) :: (b -> c) -> (a -> b) -> a -> c
(^^) f g = f . g

lit :: String -> (String -> a) -> String -> a
lit s k str1 = k (str1 ++ s)

int :: (String -> a) -> String -> Integer -> a
int k str1 n = k (str1 ++ show n)

str :: (String -> a) -> String -> String -> a
str k str1 s = k (str1 ++ s)

example :: Integer -> String
example = \n -> sprintf (lit "Ala ma " ^^ int ^^ lit " kot" ^^ str ^^ lit ".") n
            (if n == 1 then "a" else if (1 < n && n < 5) then "y" else "ow")
{-# LANGUAGE GADTs #-}

-- type Format a b = (String -> a) -> String -> b

data Format a b where
    Int    :: Format a (Integer -> a)
    Str    :: Format a (String -> a)
    Lit    :: String -> Format a a
    (:^:)  :: Format a b -> Format c a -> Format c b

-- Str :^: Int :: Format a (String -> Integer -> a)
-- Str :: Format (Integer -> a) (String -> Integer -> a)
-- Int :: Format a (Integer -> a)

eval_format :: Format a b ->  (String -> a) -> String -> b
eval_format (Lit s) = \k str1 -> k (str1 ++ s)
eval_format (Int) = \k str1 x -> k (str1 ++ show x)
eval_format (Str) = \k str1 s -> k (str1 ++ s)
eval_format (f1 :^: f2) = ef1 . ef2 where
    ef1 = eval_format f1
    ef2 = eval_format f2

ksprintf :: Format a b -> (String -> a) -> b
ksprintf f k = eval_format f k ""

-- kprintf :: Format a b -> (IO () -> a) -> b

sprintf :: Format String b -> b
sprintf f = ksprintf f id

example :: String 
example = sprintf (Lit "Hello World")

example2 :: Integer -> String
example2 = \n -> sprintf (Lit "Ala ma " :^: Int :^: Lit " kot" :^: Str :^: Lit ".") n
            (if n == 1 then "a" else if (1 < n && n < 5) then "y" else "ow")

kprintf :: Format a b -> (IO () -> a) -> b
kprintf Int con = con . putStr . show
kprintf Str con = con . putStr
kprintf (Lit s) con = con (putStr s)
kprintf (f :^: g) con = 
    kprintf f (\s1 -> 
        kprintf g (\s2 -> con (s1 >> s2)))

printf :: Format (IO ()) b -> b
printf szablon = kprintf szablon id 
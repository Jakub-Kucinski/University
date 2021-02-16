l = [2..]
f (x:xs) = [k | k <-xs, k `mod` x /= 0]
primes = map head (iterate f [2..])
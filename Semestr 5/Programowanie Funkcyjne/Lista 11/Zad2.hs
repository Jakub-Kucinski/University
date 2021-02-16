import Control.Monad

class Monad m => Random m where
    random :: m Int

newtype RS a = RS {unRS :: Int -> (Int, a)}

instance Functor (RS) where
    fmap = liftM

instance Applicative (RS) where
    pure a = RS (\i -> (i, a))
    (<*>) = ap

instance Monad (RS) where
    return = pure
    (>>=) (RS step) computeAction = RS (\initState ->
        --wykonaj krok obliczeń na początkowym stanie
        --wynikiem jest wartość pośrednia i stan pośredni
        let (interState, interValue) = step initState
        --wylicz następną akcję (zależy ona od wartości pośredniej)
            (RS nextStep) = computeAction interValue
            --wykonaj następny krok obliczeń na stanie pośrednim
            (finalState, finalValue) = nextStep interState
        --wynikiem jest wartość końcowa i stan końcowy
        in (finalState, finalValue))

instance Random (RS) where
    random = RS (\i -> let val = next_ai i in (val, val))

withSeed :: RS a -> Int -> a
withSeed (RS a) seed = snd (a seed)

next_ai :: Int -> Int
next_ai a = let b = 16807 * (a `mod` 127773) - 2836 * (a `div` 127773) in
    if b <= 0 then b + 2147483647 else b

-- withSeed (shuffle [1,2,3,4]) 1




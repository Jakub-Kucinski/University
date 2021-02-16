{-# LANGUAGE FlexibleContexts, FlexibleInstances, FunctionalDependencies #-}
import Control.Monad.State

class Monad m => BFMonad m a | m -> a where
    bfMTapeGet   :: m a
    bfMTapePut   :: a -> m ()
    bfMMoveLeft  :: m ()
    bfMMoveRight :: m ()
    bfMInput     :: m ()
    bfMOutput    :: m ()

data BF
    = MoveR
    | MoveL
    | Inc
    | Dec
    | Output
    | Input
    | While [BF]
    deriving (Eq)

coerceEnum :: (Enum a, Enum b) => a -> b
coerceEnum = toEnum . fromEnum

evalBF :: BFMonad m Integer => [BF] -> m ()
evalBF [] = return []
evalBF (b:bf) = do
    let command = case b of
        MoveR -> bfMMoveRight
        MoveL -> bfMMoveLeft
        Inc -> bfMTapeGet >>= (\x -> bfMTapePut (x+1))
        Dec -> bfMTapeGet >>= (\x -> bfMTapePut (x-1))
        Output -> bfMOutput
        Input -> bfMInput >>= bfMInput
        (While bfs) -> do
            current <- bfMTapeGet
            if current == 0
                then evalBF bf 
                else evalBF bfs >> evalBF (b:bf)
    command >> evalBF bf



import qualified QBF as QBF
import qualified NestedQBF as NestedQBF

-- pure  :: a -> Maybe a
-- (<$>) :: (a -> b) -> Maybe a -> Maybe b
-- (<*>) :: Maybe (a -> b) -> Maybe a -> Maybe b

scopeCheck :: (QBF.Var -> Maybe v) -> QBF.Formula -> Maybe (NestedQBF.Formula v)
scopeCheck env (QBF.Var var) = NestedQBF.Var <$> (env var)
scopeCheck env QBF.Bot = pure NestedQBF.Bot
scopeCheck env (QBF.Not form) = NestedQBF.Not <$> (scopeCheck env form)
scopeCheck env (QBF.And form1 form2) = NestedQBF.And <$> (scopeCheck env form1) <*> (scopeCheck env form2)
scopeCheck env (QBF.All var form) = NestedQBF.All <$> (scopeCheck (\ v -> if v == var then pure NestedQBF.Z else NestedQBF.S <$> (env v)) form)
 

scFull :: QBF.Formula -> Maybe (NestedQBF.Formula Void)
scFull = scopeCheck (const Nothing)
import Data.String
import Prelude hiding (lookup)
import qualified Data.List as List

data Expr 
    = Const Int 
    | Expr :+: Expr
    | Expr :*: Expr
    deriving Eq 

data Operation = Add | Mult deriving (Eq, Show)

data Tree 
    = Lf Int --frunza
    | Node Operation Tree Tree --ramura
    deriving (Eq, Show)

--1.1
showExpr :: Expr -> String 
showExpr (Const i) = show i
showExpr (e1 :+: e2) = "(" ++ showExpr e1 ++ "+" ++ showExpr e2 ++ ")"
showExpr (e1 :*: e2) = "(" ++ showExpr e1 ++ "*" ++ showExpr e2 ++ ")"

instance Show Expr where
    show = showExpr

--1.2
evalExp :: Expr -> Int 
evalExp (Const i) = i
evalExp (e1 :+: e2) = evalExp e1 + evalExp e2
evalExp (e1 :*: e2) = evalExp e1 * evalExp e2

exp1 :: Expr
exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 :: Expr
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 :: Expr
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 :: Expr
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)

test11 :: Bool
test11 = evalExp exp1 == 6
test12 :: Bool
test12 = evalExp exp2 == 14
test13 :: Bool
test13 = evalExp exp3 == 13
test14 :: Bool
test14 = evalExp exp4 == 16

--1.3
evalArb :: Tree -> Int 
evalArb (Lf l) = l 
evalArb (Node Add t1 t2) = evalArb t1 + evalArb t2 
evalArb (Node Mult t1 t2) = evalArb t1 * evalArb t2

--1.4
expToArb :: Expr -> Tree
expToArb (Const i) = Lf i
expToArb (e1 :+: e2) = Node Add (expToArb e1) (expToArb e2)
expToArb (e1 :*: e2) = Node Mult (expToArb e1) (expToArb e2)

--1.5
class MySmallCheck a where
    smallValues :: [a]
    smallCheck :: (a -> Bool) -> Bool 
    smallCheck prop = and [prop x | x <- smallValues]

--1.6
checkExp :: Expr -> Bool 
checkExp exp = (evalExp exp) == evalArb (expToArb exp)

--2 (Clasa Collection)
type Key = Int 
type Value = String 

class Collection c where
    empty :: c
    singleton :: Key -> Value -> c
    insert :: Key -> Value -> c -> c 
    delete :: Key -> c -> c 
    lookup :: Key -> c -> Maybe Value
    toList :: c -> [(Key, Value)]
    --2.1
    keys :: c -> [Key]
    keys col = [fst el | el <- toList col]
    values :: c -> [Value]
    values col = [snd el | el <- toList col]
    fromList :: [(Key, Value)] -> c
    fromList [] = empty
    fromList list = insert (fst h) (snd h) (fromList t)
        where 
            h = head list
            t = tail list

--2.2
newtype PairList
    = PairList {getPairList :: [(Key, Value)]}

instance Collection PairList where
    empty = PairList []
    singleton k v = PairList [(k, v)]
    insert k v (PairList l) = PairList ((k, v) : filter ((/=k).fst) l)
    delete k (PairList l) = PairList(filter (\x -> fst x /= k) l)
    --lookup k (PairList l)
    --    | length list /= 0 = Just snd (list !! 0)
    --    | otherwise = Nothing
    --    where list = (filter ((/=k).fst) l)
    toList = getPairList

--2.3
data SearchTree
  = Empty
  | Nod
    SearchTree    -- elemente cu cheia mai mica
    Key           -- cheia elementului
    (Maybe Value) -- valoarea elementului
    SearchTree    -- elemente cu cheia mai mare
  deriving Show

instance Collection SearchTree where
    empty = Empty
    singleton k v = Nod Empty k (Just v) Empty
    insert k v Empty = Nod Empty k (Just v) Empty
    insert k v (Nod t1 ky val t2) = 
        if k > ky then insert k v t2 
        else if k < ky then insert k v t1 
        else Nod t1 k (Just v) t2
    delete k (Nod t1 ky val t2) = 
        if k < ky then delete k t1 
        else if k > ky then delete k t2 
        else Nod t1 k Nothing  t2
    lookup k (Nod t1 ky val t2) = 
        if k < ky then lookup k t1 
        else if k > ky then lookup k t2 
        else val 
    toList Empty = []
    toList (Nod t1 k (Just v) t2) = toList t1 ++ [(k, v)] ++ toList t2
    toList (Nod t1 k Nothing  t2) = toList t1 ++ [] ++ toList t2 
    keys c = [fst p | p <- toList c] -- lista cu toate cheile
    values c = [snd p | p <- toList c] -- lista cu toate valorile
    fromList [] = empty
    fromList ((k, v) : t) = insert k v (fromList t)


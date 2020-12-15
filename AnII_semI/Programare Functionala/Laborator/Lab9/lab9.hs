
import           Prelude hiding (lookup)
import qualified Data.List as List

data Expr = Const Int -- integer constant
            |Expr :+: Expr -- addition
            |Expr :*: Expr -- multiplication
            deriving Eq
data Operation = Add | Mult deriving (Eq, Show)
data Tree = Lf Int -- leaf
            |Node Operation Tree Tree -- branch
            deriving (Eq, Show)

instance Show Expr where
    show (Const l) = show l
    show (e1 :+: e2) = "(" ++ show e1 ++ "+" ++ show e2 ++ ")"
    show (e1 :*: e2) = "(" ++ show e1 ++ "*" ++ show e2 ++ ")"

evalExp :: Expr -> Int
evalExp (Const x) = x
evalExp (e1 :+: e2) = evalExp e1 + evalExp e2
evalExp (e1 :*: e2) = evalExp e1 * evalExp e2


evalArb :: Tree -> Int
evalArb (Lf n) = n
evalArb (Node Add arb1 arb2) = evalArb(arb1) + evalArb(arb2)
evalArb (Node Mult arb1 arb2) = evalArb(arb1) * evalArb(arb2)

expToArb::Expr->Tree
expToArb (Const lf)=Lf lf
expToArb (l:+:g)=Node Add (expToArb l) (expToArb g)
expToArb (l:*:g)=Node Mult (expToArb l) (expToArb g)

arb1 :: Tree
arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 :: Tree
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 :: Tree
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 :: Tree
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 :: Bool
test21 = evalArb arb1 == 6
test22 :: Bool
test22 = evalArb arb2 == 14
test23 :: Bool
test23 = evalArb arb3 == 13
test24 :: Bool
test24 = evalArb arb4 == 16

class MySmallCheck a where
     smallValues :: [a]
     smallCheck :: ( a -> Bool ) -> Bool
     smallCheck prop = and [ prop x | x <- smallValues ]

checkExp :: Expr -> Bool
checkExp expr = evalExp(expr) == evalArb(expToArb(expr))






class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert
      :: Ord key
      => key -> value -> c key value -> c key value
  lookup :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  values :: c key value -> [value]
  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key,value)] -> c key value

newtype PairList k v
  = PairList { getPairList :: [(k, v)] }

data SearchTree key value
  = Empty
  | Node
      (SearchTree key value) -- elemente cu cheia mai mica 
      key                    -- cheia elementului
      (Maybe value)          -- valoarea elementului
      (SearchTree key value) -- elemente cu cheia mai mare

type Key = Int
type Value = String
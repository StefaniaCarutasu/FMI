import Data.Char
import Data.Text
import Data.String
import Data.List

type Nume = String
data Prop 
    = Var Nume
    | F
    | T 
    | Not Prop
    | Prop :|: Prop
    | Prop :&: Prop
    deriving Eq
infixr 2 :|:
infixr 2 :&:

--ex1
--1
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

--2
p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

--3
p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))


--ex2
{-showProp :: Prop -> String
showProp (Var x) = x
showProp F = "False"
showProp T = "True"
showProp (Not p) = "(" ++ "~" ++ showProp p ++ ")"
showProp (p :|: q) = "(" ++ showProp p ++ "|" ++ showProp q ++ ")"
showProp (p :&: q) = "(" ++ showProp p ++ "&" ++ showProp q ++ ")"

instance Show Prop where
show = showProp-}

--ex2'
{-instance Show Prop where
  show (Var x) = x
  show F = "False"
  show T = "True"
  show (Not (Var p)) = "~" ++ show (Var p)
  show (Not p) = "~(" ++ show p ++ ")"
  show ((p :|: s) :&: (q :|: t)) = "(" ++ show (p :|: s) ++ ")&(" ++ show (q :|: t) ++ ")"
  show (p :&: (q :|: t)) = show p ++ "&(" ++ show (q :|: t) ++ ")"
  show ((p :|: s) :&: q) = "(" ++ show (p :|: s) ++ ")&" ++ show q
  show (p :&: q) = show p ++ "&" ++ show q
  show (p :|: q) = show p ++ "|" ++ show q -}


showProp1 :: Prop -> String
showProp1 (Var p) = p
showProp1 F = "False"
showProp1 T = "True"
showProp1 (Not (Var p)) = "~" ++ showProp1 (Var p)
showProp1 (Not p) = "(~" ++ showProp1 p ++ ")"
showProp1 ((p :|: s) :&: (q :|: r)) = "(" ++ showProp1 (p :|: s) ++ ")&(" ++ showProp1 (q :|: r) ++ ")"
showProp1 (p :&: (q :|: r)) = showProp1 p ++ "(&" ++ showProp1 (q :|: r) ++ ")"
showProp1 ((p :|: s) :&: q) = "(" ++ showProp1 (p :|: s) ++ ")&" ++ showProp1 q
showProp1 (p :|: q) = showProp1 p ++ "|" ++ showProp1 q
showProp1 (p :&: q) = showProp1 p ++ "&" ++ showProp1 q
 
instance Show Prop where
show = showProp1

--ex4
variabile :: Prop -> [Nume]
variabile (Var p) = [p]
variabile (Not p) = nub (variabile p)
variabile (p :&: q) = nub (variabile p) ++ variabile q
variabile (p :|: q) = nub (variabile p) ++ variabile q
variabile _ = []
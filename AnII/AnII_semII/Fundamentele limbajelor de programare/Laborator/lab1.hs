--Limbajul unui mini calculator
data Prog = On Instr
data Instr = Off | Expr :> Instr
data Expr = Mem | V Int | Expr :+ Expr
type Env = Int 
type DomProg = [Int]
type DomInstr = Env -> [Int ]
type DomExpr = Env -> Int 

--Exercitiu
prog :: Prog -> DomProg
prog (On instr) = stmt instr 0

stmt :: Instr -> DomInstr
stmt Off _ = []
stmt (exp :> instr) m = let 
                            v = expr exp m 
                        in
                            (v : (stmt instr v))    

expr :: Expr -> DomExpr
expr Mem m = m
expr (V val) _ = val
expr (exp1 :+ exp2) m = expr exp1 m + expr exp2 m


--Mini-Haskell
type Name = String 
data Hask = HTrue
            | HFalse
            | HLit Int 
            | HIf Hask Hask Hask
            | Hask :==: Hask
            | Hask :+: Hask
            | HVar Name 
            | HLam Name Hask
            | Hask :$: Hask
    deriving(Read, Show)
infix 4 :==:
infixl 6 :+:
infixl 9 :$:

data Value = VBool Bool 
            | VInt Int 
            | VFun (Value -> Value)
            | VError --pentru interpretarea erorilor
type HEnv = [(Name, Value)]
type DomHask = HEnv -> Value --domeniul de evaluare al expresiilor

--a (Instantiere show pentru value)
instance Show Value where
    show (VBool b) = show b
    show (VInt i) = show i 
    show (VFun f) = "Functie"
    show VError = "Eroare"

--b (Instantiere Eq pt value)
instance Eq Value where
    (VBool b1) == (VBool b2) = b1 == b2
    (VInt i1) == (VInt i2) = i1 == i2
    _ == _ = error "Nu se pot compara"

--c (Evaluarea unei expr de tip Hask)
hEval :: Hask -> DomHask
hEval HTrue env = VBool True 
hEval HFalse env = VBool False 
hEval (HLit nr) env = VInt nr
hEval (HIf exp1 exp2 exp3) env
  | hEval exp1 env == VBool True = hEval exp2 env
  | hEval exp1 env == VBool False = hEval exp3 env
  | otherwise = VError
hEval (exp1 :==: exp2) env = VBool (hEval exp1 env == hEval exp2 env)
hEval (exp1 :+: exp2) env = let 
                              nr1 = hEval exp1 env 
                              nr2 = hEval exp2 env
                            in
                              case (nr1, nr2) of
                                ((VInt n1), (VInt n2)) -> VInt (n1 + n2)
                                _ -> VError
hEval (HVar nume) env = let
                          val = lookup nume env
                        in 
                          case val of
                            (Just v) -> v
                            Nothing -> VError
--hEval (HVar nume) env = fromMaybe VError (lookup nume env)
hEval (HLam nume exp) env = VFun (\v -> hEval exp ((nume, v) : env))
hEval (exp1 :$: exp2) env = let
                              func = hEval exp1 env
                              nr = hEval exp2 env
                            in
                              case func of
                                (VFun f) -> f nr
                                _ -> VError

h0 = (HLam "x" (HLam "y" ((HVar "x") :+: (HVar "y"))))
      :$: (HLit 3)
      :$: (HLit 4)
test_h0 = hEval h0 [] == VInt 7

h2 = hEval (HIf HTrue (HVar "x":+: HVar "y") (HVar "x")) [("x",VInt 2),("y", VInt 30)] -- 32
h3 = hEval (HIf HFalse (HVar "x":+: HVar "y") (HVar "x")) [("x",VInt 2),("y", VInt 30)] -- 2
h4 = hEval (HIf (HFalse:==:HTrue) (HVar "x":+: HVar "y") (HVar "x")) [("x",VInt 2),("y", VInt 30)] -- 2
h5 = hEval (HIf (HFalse:==:HVar "x") (HVar "x":+: HVar "y") (HVar "x")) [("x",VInt 2),("y", VInt 30)] -- *** Exception: Nu se pot compara
h6 = hEval (HVar "x") [("x",VInt 2),("y", VInt 30)] -- 2
h7 = hEval (HVar "x") [("z",VInt 2),("y", VInt 30)] -- eroare

import Data.Maybe ()
import Data.List ()

type Name = String 
data Pgm = Pgm [Name] Stmt 
        deriving (Read, Show)

data Stmt = Skip | Stmt ::: Stmt | If BExp Stmt Stmt | While BExp Stmt | Name := AExp
        deriving (Read, Show)

data AExp = Lit Integer | AExp :+: AExp | AExp :*: AExp | Var Name
        deriving (Read, Show)

data BExp = BTrue | BFalse | AExp :==: AExp | Not BExp
        deriving (Read, Show)

infixr 2 :::
infix 3 :=
infix 4 :==:
infixl 6 :+:
infixl 7 :*:

type Env = [(Name, Integer)]

factStmt :: Stmt
factStmt =
    "p" := Lit 1 ::: "n" := Lit 3:::
    While (Not (Var "n" :==: Lit 0))
        ( "p" := Var "p" :*: Var "n" :::
          "n" := Var "n" :+: Lit (-1)
        )       
pg1 :: Pgm
pg1 = Pgm [] factStmt

--Functiile de evaluare pt Pgm, Stmt, AExp, BExp
aEval :: AExp -> Env -> Integer 
aEval (Lit nr) env = nr
aEval (e1 :+: e2) env = (aEval e1 env) + (aEval e2 env)
aEval (e1 :*: e2) env = (aEval e1 env) * (aEval e2 env)
aEval (Var nume) env = let
                            val = lookup  nume env
                        in 
                            case val of
                                (Just v) -> v
                                Nothing -> error "Variabila nu este initializata"

bEval :: BExp -> Env -> Bool 
bEval BTrue env = True 
bEval BFalse env = False 
bEval (e1 :==: e2) env = (aEval e1 env) == (aEval e2 env)
bEval (Not b) env = not (bEval b env)

sEval :: Stmt -> Env -> Env
sEval Skip env = env
sEval (e1 ::: e2) env = sEval e2 (sEval e1 env)
sEval (If e e1 e2) env =
    if bEval e env then sEval e1 env
    else sEval e2 env
sEval (While e e1) env = 
    if bEval e env then sEval (While e e1) (sEval e1 env)
    else env  
sEval (n := a) env = [(var, val) | (var, val) <- env, var /= n] ++ [(n, aEval a env)]

pEval :: Pgm -> Env
pEval (Pgm list stmt) = sEval stmt [(variabila, 0)| variabila <- list]








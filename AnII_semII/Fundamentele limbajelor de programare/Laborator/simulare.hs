{-
Gasiti mai jos  un minilimbaj. Interpretarea este partial definita.
Un program este o expresie de tip `Pgm`iar rezultatul executiei este ultima stare a memoriei. 
Executia unui program se face apeland `pEval`.
-}

import Data.Maybe
import Data.List

type Name = String

data  Pgm  = Pgm [Name] Stmt
        deriving (Read, Show)

data Stmt = Skip | Stmt ::: Stmt | If BExp Stmt Stmt| Name := AExp | While BExp Stmt
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


{-
--a,b 
aEval :: AExp -> Env -> Integer
aEval (Var name) env = case lookup name env of
                            Just val -> val
                            Nothing -> error "Nu exista"
aEval (Lit i) env = i
aEval (e1 :+: e2) env = aEval e1 env + aEval e2 env
aEval (e1 :*: e2) env = aEval e1 env * aEval e2 env




bEval :: BExp -> Env -> Bool
bEval BTrue env = True
bEval BFalse env = False
bEval (e1 :==: e2) env = aEval e1 env == aEval e2 env
bEval (Not e) env = not (bEval e env)


sEval :: Stmt -> Env -> Env
sEval Skip env = env
sEval (st1 ::: st2) env = sEval st2 (sEval st1 env)
sEval (If b st1 st2) env =  if bEval b env then sEval st1 env else sEval st2 env
sEval (x := e) env = (x, aEval e env) : [(var, val) | (var, val) <- env, var /= x]
sEval (While b st) env = if bEval b env then sEval (While b st) (sEval st env) else env 
                            



pEval :: Pgm -> Env
pEval (Pgm lvar st) = sEval st [(var, 0) | var <- lvar]



factStmt :: Stmt
factStmt =
  "p" := Lit 1 ::: "n" := Lit 3 :::
  While (Not (Var "n" :==: Lit 0))
    ( "p" := Var "p" :*: Var "n" :::
      "n" := Var "n" :+: Lit (-1)
    )

test1 = Pgm [] factStmt

-}

--c

aEval :: AExp -> Env -> (AExp, Integer)
aEval (Var name) env = case lookup name env of
                            Just val -> (Var name, val)
                            Nothing -> error "Nu exista"
aEval (Lit i) env = (Lit i, i)
aEval (e1 :+: e2) env = (e1 :+: e2, snd (aEval e1 env) + snd (aEval e2 env))
aEval (e1 :*: e2) env = (e1 :*: e2, snd (aEval e1 env) * snd (aEval e2 env))


bEval :: BExp -> Env -> (BExp, Bool)
bEval BTrue env = (BTrue, True)
bEval BFalse env = (BFalse, False)
bEval (e1 :==: e2) env = (e1 :==: e2, snd (aEval e1 env) == snd (aEval e2 env))
bEval (Not e) env = let val = snd (bEval e env) in (Not e, not val)


sEval :: Stmt -> Env -> Env
sEval Skip env = env
sEval (st1 ::: st2) env = sEval st2 (sEval st1 env)
sEval (If b st1 st2) env =  if snd (bEval b env) then sEval st1 env else sEval st2 env
sEval (x := e) env = (x, snd (aEval e env)) : [(var, val) | (var, val) <- env, var /= x]
sEval (While b st) env = if snd (bEval b env) then sEval (While b st) (sEval st env) else env 
                            

pEval :: Pgm -> Env
pEval (Pgm lvar st) = sEval st [(var, 0) | var <- lvar]

{-CERINTE

1) (10pct) Finalizati definitia functiilor de interpretare.
2) (10pct) Adaugati instructiunea `While BExp Stmt` si interpretarea ei.
3) (20pct) Definiti interpretarea limbajului astfel incat programele sa se execute dintr-o stare 
initiala data iar  `pEval`  sa afiseze starea initiala si starea finala.    

Definiti teste pentru verificarea solutiilor si indicati raspunsurile primite. 

-}
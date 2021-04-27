import Data.Maybe
import Data.Char
import System.Random
import Data.List

type Nume = String 
data Prop 
    =Var Nume
    | F
    | T
    | Not Prop
    | Prop :|: Prop
    | Prop :&: Prop
    | Prop :->: Prop
    | Prop :<->: Prop
    deriving Eq
infixr 2 :|:
infixr 3 :&:
infixr 4 :->:
infixr 5 :<->:
--Ex1
--1
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

--2
p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not(Var "P") :&: Not(Var "Q"))

--3
p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not(Var "P") :|: Not(Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))

--Ex2
showProp :: Prop -> String
showProp (Var x) = x
showProp F = "False"
showProp T = "True"
showProp (Not p) = "(" ++ "~" ++ showProp p ++ ")"
showProp (p :|: q) = "(" ++ showProp p ++ "|" ++ showProp q ++ ")"
showProp (p :&: q) = "(" ++ showProp p ++ "&" ++ showProp q ++ ")"
showProp (p :->: q) = "(" ++ showProp p ++ "->" + showProp q ++ ")"
showProp (p :<->: q) = "(" ++ showProp p ++ "<->" + showProp q ++ ")"

instance Show Prop where
    show = showProp
test_ShowProp :: Bool
test_ShowProp = show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]   --lista de atribuiri de valori de adevar pt numele variabilelor

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a
eval :: Prop -> Env -> Bool
eval (Var p) e = impureLookup p e
eval F e = False 
eval T e = True 
eval (Not p) e = not (eval p e)
eval (p :&: q) e = (eval p e) && (eval q e)
eval (p :|: q) e = (eval p e) || (eval q e)
eval (p :->: q) e = (eval (Not p) :|: q) e
eval (p :<->: q) e = eval ((p :->: q) :&: (q :->: p)) e 

test_eval = eval (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

--Satisfiabilitate
--4
variabile :: Prop -> [Nume]
variabile prop = nub (variabile' prop)
    where
        variabile' :: Prop -> [Nume]
        variabile' F = []
        variabile' T = []
        variabile' (Var p) = [p]
        variabile' (Not p) = variabile' p
        variabile' (p :|: q) = variabile' p ++ variabile' q
        variabile' (p :&: q) = variabile' p ++ variabile' q
        variabile' (p :->: q) = variabile' p ++ variabile' q
        variabile' (p :<->: q) = variabile' p ++ variabile' q

--5
envs :: [Nume] -> [Env]
envs [] = [[]]
envs (x : xs) = [(x, val) : e | val <-[False, True], e <- envs xs]

--6

satisfiabila :: Prop -> Bool
satisfiabila prop = foldr (||) False (map (\e -> eval prop e) (envs (variabile prop)))

--7
valida :: Prop -> Bool
--valida prop = foldr (&&) True (map (\e -> eval prop e) (envs (variabile prop)))
valida prop = satisfiabila (Not prop) == False

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

--8
tabelAdevar :: Prop -> String
tabelAdevar prop = concat [x ++ " " | x <- varabile prop] ++ show prop ++ "\n" ++ valori prop 0
    where
        valori :: Prop -> Int -> String
        valori prop nr
            | nr >= length (envs (variabile prop)) = ""
            | otherwise = let 
                      e = envs (variabile prop)
                    in
                      concat [val (snd x) ++ " " | x <- (e !! nr)] ++ val (eval prop (e !! nr)) ++ "\n" ++ valori prop (nr + 1)
                        where val :: Bool -> String
                              val True = "T"
                              val False = "F"

--10
echivalenta :: Prop -> Prop -> Bool
echivalenta p1 p2 = foldr (&&) True [eval (p1 :<->: p2) (e1 ++ e2) | e1 <- envs (variabile p1), e2 <- envs (variabile p2)]




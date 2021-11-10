--variant 1 esuata
{-main = do
    putStrLn "Alege prima mutare"     --cout
    mutare1 <- getLine     --cin
    putStrLn ("Mutarea ta este " ++ mutare1)
    putStrLn "Alege a doua mutare"     --cout
    mutare2 <- getLine     --cin
    putStrLn ("Mutarea ta este " ++ mutare2)
    --joc :: String -> String -> String
    joc = 
        | (mutare1 == mutare2) = "Egalitate"
        | (mutare1 == "Piatra") && (mutare2 == "Foarfeca")|| (mutare1 == "Foarfeca") && (mutare2 == "Hartie") || (mutare1 == "Hartie") && (mutare2 == "Piatra") = "Victorie"
        | otherwise =  "Infrangere"-}

--varianta lui Radu esuata
{-data Alegere=Piatra| Foarfeca| Hartie deriving(Eq,Show)
data Rezultat=Victorie| Infrangere| Egalitate deriving(Eq,Show)
partida::Alegere->Alegere->Rezultat
partida x y=if(x==y) then Egalitate
            else if x==Piatra && y==Foarfeca||
                    x==Foarfeca && y==Hartie||
                    x==Hartie && y==Piatra then Victorie
            else Infrangere  -} 

--varianta care merge
data Alegere=Piatra| Foarfeca| Hartie deriving(Eq,Show)
data Rezultat=Victorie| Infrangere| Egalitate deriving(Eq,Show)
joc :: Alegere -> Alegere -> Rezultat
joc x y  
    | x == y = Egalitate 
    | (x == Piatra) && (y == Foarfeca)|| (x == Foarfeca) && (y == Hartie) || (x == Hartie) && (y == Piatra) = Victorie
    | otherwise Infrangere  
main = putStrLn (show (joc Piatra Foarfeca)) 
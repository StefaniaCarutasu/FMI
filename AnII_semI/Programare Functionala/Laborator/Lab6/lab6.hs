data Fruct
    = Mar String Bool
    |Portocala String Int

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala "Tarocco" _) = True
ePortocalaDeSicilia (Portocala "Moro" _) = True
ePortocalaDeSicilia (Portocala "Sanguinello" _) = True
ePortocalaDeSicilia _ = False

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia l = sum [nr | (Portocala s nr) <- l, ePortocalaDeSicilia (Portocala s nr)]

nrMereViermi :: [Fruct] -> Int
nrMereViermi list = length [(Mar s b) | (Mar s b) <- list, b == True]

--Ex2
data Linie = L [Int]
    deriving Show
data Matrice = M [Linie]

--a
verifica :: Matrice -> Int -> Bool
verifica (M matrix) n = foldr (&&) True [sum l == n | (L l) <- matrix]

--c
pozitive :: [Int] -> Bool
pozitive l = foldr (&&) True [x > 0 | x <- l]
doarPozN :: Matrice -> Int -> Bool
doarPozN (M matrix) n = foldr (&&) True (map pozitive [l | (L l) <- matrix, length l == n])
    
--b
arataL :: Linie -> [String]
arataL (L lista) = [printList lista]
    where
        printList :: [Int] -> String
        printList [] = ""
        printList (h:t) = show h ++ " " ++ printList t

arataM :: Matrice -> [String]
arataM (M[]) = []
arataM (M lista) = printMat lista
    where
        printMat :: [Linie] -> [String]
        printMat [] = []
        printMat (h:t) = arataL h ++ printMat t

instance Show Matrice where
    show (M(lista)) = unlines (arataM (M(lista)))

instance Show Linie where
    show (L l) = foldr (++) "" (map (\x ->( (show x)++" ")) l)

instance Show Matrice where
    show (M l) = foldr (++) "" (map (\x ->( (show x)++"\n")) l)


showLinie :: [Int] -> String
showLinie [] = []
showLinie (x : xs) = show x ++ " " ++ showLinie xs

showMatrice :: [Linie] -> String
showMatrice [] = []
showMatrice ((L x) : xs) = showLinie x ++ "\n" ++ showMatrice xs

instance Show Matrice where
   show (M(list)) = showMatrice(list)
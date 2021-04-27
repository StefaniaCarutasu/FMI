--Curs 6

data Point a b = Pt a b

pr1 :: Point a b -> a
pr1 (Pt x _) = x

pr2 :: Point a b -> b 
pr2 (Pt _ y) = y

{-data List a = Nil | Cons a (List a)
append :: List a -> List a -> List a
append Nil ys = ys
append (Cons x xs) ys = Cons x (append xs ys)-}

data StrInt = VS String | VI Int 
data Shape = Circle Float | Rectangle Float Float

data Tree a = Empty | Leaf a | Branch (Tree a) (Tree a)

data List a = Nil 
            | a ::: List a
        deriving (Show)

--Liste
--data [a] = [] | a : [a]

--Tupluri
--data (a, b) = (a, b)
--data (a, b, c) = (a, b, c)

type LastName = String
type FirstName = String
type Age = Int
type Height = Float
type Phone = String

--data Person = Person FirstName LastName Age Height Phone

data Person = Person {
    firstName :: String,
    lastName :: String,
    age :: Int,
    height :: Float,
    phoneNumber :: String
}
    deriving (Show)
ionel = Person "Ion" "Ionescu" 23 178 "07217217"
nextYear :: Person -> Person
nextYear person = person {age = age person + 1}

--Lab6

data Fruct 
    = Mar String Bool
    | Portocala String Int
    deriving Show

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10

--ex1
--a
ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala soi _) = 
    if soi == "Tarocco" || soi == "Moro" || soi == "Sanguinello" then True
    else False
    
--b
nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia listaFructe = sum[nr | (Portocala soi nr) <- listaFructe, ePortocalaDeSicilia(Portocala soi nr) ]

--c
nrMereViermi :: [Fruct] -> Int
nrMereViermi l = length[soi | (Mar soi True) <- l]

--ex2
data Linie = L [Int]
data Matrice = M [Linie]
--a
verifica (M matrice) n = foldr (&&) True [sum l == n | (L l) <- matrice]


--b
showLinie :: [Int] -> String
showLinie [] = []
showLinie (x : xs) = show x ++ " " ++ showLinie xs

showMatrice :: [Linie] -> String
showMatrice [] = []
showMatrice ((L x) : xs) = showLinie x ++ "\n" ++ showMatrice xs

instance Show Matrice where
   show (M(list)) = showMatrice(list)

--c
pozitive :: [Int] -> Bool
pozitive l = foldr (&&) True [x > 0 | x <- l]
doarPozN :: Matrice -> Int -> Bool
doarPozN (M matrix) n = foldr (&&) True (map pozitive [l | (L l) <- matrix, length l == n])



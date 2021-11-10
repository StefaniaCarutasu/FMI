--lab1
import Data.List
import Data.Char

x = permutations [1, 2, 3]
y = permutations "abc"

maxim :: Integer -> Integer -> Integer
maxim x y = 
    if (x > y) 
        then x 
        else y

{-maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z = maxim x (maxim y z)

maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z = 
    if (x > y && x > z) then x
    else if (y > x && y > z) then y
    else z-}

maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z = let u = (maxim x y) in (maxim u z)

maxim4 :: Integer -> Integer -> Integer -> Integer -> Integer
maxim4 x y z t = 
    let u = maxim3 x y z
    in maxim u t

data Alegere
    = Piatra
    | Foarfeca
    | Hartie
    deriving(Eq, Show)
data Rezultat
    = Victorie
    | Infrangere
    | Egalitate
    deriving(Show)

partida :: Alegere -> Alegere -> Rezultat
partida x y = 
    if x == y then Egalitate
    else if (x == Piatra && y == Foarfeca) || (x == Foarfeca && y == Hartie) || (x == Hartie && y == Piatra) then Victorie
    else Infrangere

--lab2
fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n = 
    if n < 2 then n 
    else fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)

semiPare :: [Int] -> [Int]
semiPare x = 
    if null x then x
    else if (head x) `mod` 2 == 0 then (head x) `div` 2 : semiPare (tail x)
    else semiPare (tail x)
l :: [Int]
--l = semiPare [0,2,1,7,8,56,17,18]

semiPareComp :: [Int] -> [Int]
semiPareComp l = [div x 2 | x <- l, mod x 2 == 0 ]
l = semiPare [0,2,1,7,8,56,17,18]

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp x y l = [t | t <- l, x <= t, t <= y]

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec x y l = 
    if null l then l
    else if x <= head l && head l <= y then head l : inIntervalRec x y (tail l)
    else inIntervalRec x y (tail l)

pozitiveRec :: [Int] -> Int
pozitiveRec l = 
    if null l then 0
    else if head l > 0 then 1 + pozitiveRec (tail l)
    else pozitiveRec (tail l)

{-pozitiveComp :: [Int] -> Int
pozitiveComp l = length[x| x <- l, x > 0] -}

{-pozCurenta :: [Int] -> [(Int, Int)] 
pozCurenta l = zip [0..] l

pozitiiImpareRec :: [(Int, Int)] -> [Int]
pozitiiImpareRec pozCurenta l = 
    if null l then []
    else if odd snd h then fst h : pozitiiImpareRec t'
    else pozitiiImpareRec t'
    where
        h = head l
        t' = tail (pozCurenta l)-}

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [snd x | x <- zip l [0..], mod (fst x) 2 == 1]

multDigitsRec :: [Char] -> Int
multDigitsRec l = 
    if null l then 1
    else if isDigit (head l) then digitToInt (head l) * multDigitsRec (tail l)
    else multDigitsRec (tail l)

multDigitsComp :: String -> Int
multDigitsComp str = product[digitToInt x | x <- str, isDigit x]  

discountRec :: [Float] -> [Float]
discountRec l =
    if null l then l
    else if 0.75 * h < 200 then 0.75 * h : discountRec t
    else discountRec t
    where
        h = head l
        t = tail l

discountComp :: [Float] -> [Float]
discountComp l = [ 0.75 * x | x <- l, 0.75 * x < 200]

--lab3
k :: [Int]
k = [x ^ 2 | x <- [1..10], x `mod` 3 == 2]

factori :: Int -> [Int]
factori n = [x | x <- [2..n `div`2], n `mod` x == 0]

prim :: Int -> Bool
prim n = length (factori n) == 0

numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x == True]

{-lungMin :: [a] -> [a] -> [a] -> Int
lungMin x y z = 
    if length x < length y && length x < length z then length x
    else if length y < length x && length y < length z then length y
    else length z-}

myzip3 :: [a] -> [a] -> [a] -> [(a, a, a)]
myzip3 x y z = [(x !! i, y !! i, z !! i) | i <- [0..((min (length x) (min (length y) (length z))) - 1)]]

--map
firstEl :: [(a,b)] -> [a]
firstEl l = map fst l

sumList :: [[Integer]] -> [Integer]
sumList l = map (sum) l

prel2 :: [Integer] -> [Integer]
prel2 l = map (`div` 2) [x | x <- l, mod x 2 == 0] ++ map (*2) [y | y <- l, mod y 2 == 1 ]

auxPrel :: Integer -> Integer
auxPrel n = 
    if mod n 2 == 0 then n `div` 2
    else n * 2

prel3 :: [Integer] -> [Integer]
prel3 l = map auxPrel l


--map + filter
isElem :: Char -> [String]->[String]
isElem c lista = filter (c `elem`) lista

patrateImpare :: [Integer] -> [Integer]
patrateImpare l = map (^2) (filter odd l)

patratePozImpare :: [Integer] -> [Integer]
patratePozImpare l = map (^2) [fst x | x <- zip l [0..], snd x `mod` 2 == 1]

--lab4
--foldr
produsRec :: [Integer] -> Integer
produsRec l = 
    if null l then 1
    else head l * produsRec (tail l)
produsFold :: [Integer] -> Integer
produsFold l = foldr (*) 1 l


andRec :: [Bool] -> Bool
andRec l =
    if null l then True
    else if head l == True then head l && and (tail l)
    else False
andFold :: [Bool] -> Bool
andFold l = foldr (&&) True l


concatRec :: [[a]] -> [a]
concatRec l = 
    if null l then []
    else head l ++ concatRec (tail l)
concatFold :: [[a]] -> [a]
concatFold l = foldr (++) [] l


rmChar :: Char -> String -> String
rmChar c str = 
    if null str then ""
    else if head str == c then rmChar c (tail str)
    else (head str) : rmChar c (tail str)
rmCharsRec :: String -> String -> String
rmCharsRec str1 str2 =
    if null str1 then str2
    else rmCharsRec (tail str1) (rmChar (head str1) str2)
test_rmchars :: Bool
test_rmchars = rmCharsRec ['a' .. 'l'] "fotbal" == "ot"


rmCharsFold :: String -> String -> String
rmCharsFold s1 s2 = foldr rmChar s2 s1
test_rmcharsf :: Bool
test_rmcharsf = rmCharsFold ['a' .. 'l'] "fotbal" == "ot"

--functii de nivel inalt
nrPrim :: Int -> Bool
nrPrim n = length [x | x <- [2..(n `div` 2)], n `mod` x == 0] == 0

numerePrimeCiur :: Int -> [Int]
numerePrimeCiur n = [x | x <-[1..n], nrPrim x == True]


{-ordonataNat :: [Int] -> Bool
ordonataNat l = foldr (&&) True [l !! i < l !! (i + 1)| i <- [0..(length l -2)]]
ordonataNat :: [Int] -> Bool
ordonataNat l = and [l !! i < l !! (i + 1)| i <- [0..(length l -2)]]-}
ordonataNat :: [Int] -> Bool
ordonataNat l = and [fst x < snd x | x <- zip l (tail l)]


ordonataNat1 :: [Int] -> Bool
ordonataNat1 l = 
    if length l == 1 then True
    else if head l < head (tail l) then True && ordonataNat1 (tail l)
    else False

ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata l relatie = and [relatie (l !! i) (l !! (i + 1)) | i <- [0..(length l -2)]]

--definire operatori
(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool
(*<*) (x,y) (z,t) = x > t && y < z

compuneList :: (b -> c) -> [(a -> b)] -> [(a -> c)]
compuneList f lf = map (f.) lf

aplicaList :: a -> [(a -> b)] -> [b]
aplicaList nr lf = [f nr | f <- lf]

--lab5
sumaPatrateImpareRec ::[Int] -> Int
sumaPatrateImpareRec l =
    if null l then 1
    else if odd h then h^2 + sumaPatrateImpareRec t 
    else sumaPatrateImpareRec t 
    where 
        h = head l
        t = tail l
sumaPatrateImpareFold :: [Int] -> Int
sumaPatrateImpareFold l = foldr (+) 0 [x^2 | x <- l, odd x]


semn :: [Integer] -> String
semn l =
    if null l then "" 
    else if h == 0 then '0' : semn t 
    else if h < 0 && h > -10 then '-' : semn t 
    else if h > 0 && h < 10 then '+' : semn t 
    else semn t 
    where 
        h = head l 
        t = tail l 
semnNr :: Integer -> String
semnNr n = 
    if n == 0 then "0"
    else if n < 0 then "-"
    else "+"
semnFold :: [Integer] -> String
semnFold l = foldr (++) "" [(semnNr k) | k <- l, -9 <= k, k <= 9]

corect :: [[a]] -> Bool
corect m = foldr (&&) True [length (m !! i) == length (m !! (i + 1)) | i <- [0..(length m - 2)]]


el :: [[a]] -> Int -> Int -> a
el m i j = (m !! i) !! j


transforma :: [[a]] -> [(a, Int, Int)]
transforma m = [(el m i j, i, j) | i <- [0..(length m -1)], j <- [0..(length (m !! i) - 1)] ]


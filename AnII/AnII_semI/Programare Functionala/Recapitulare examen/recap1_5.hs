import Data.List
import Data.Char

--lab2
--recursie
semiPareRec :: [Int] -> [Int]
semiPareRec l = 
    if l == [] then []
    else if (head l) `mod` 2 == 0 then (head l) `div` 2 : semiPareRec (tail l)
    else semiPareRec (tail l)

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec x y l = 
    if l == [] then []
    else if x <= (head l) && (head l) <= y then (head l) : inIntervalRec x y (tail l)
    else inIntervalRec x y (tail l)

pozitiveRec :: [Int] -> Int
pozitiveRec l = 
    if l == [] then 0
    else if (head l) > 0 then 1 + pozitiveRec (tail l)
    else 0 + pozitiveRec (tail l)

pozitiiImpareRec :: [Int] -> Int -> [Int]
pozitiiImpareRec l poz = 
    if l == [] then []
    else if mod (head l) 2 == 1 then poz : pozitiiImpareRec (tail l) (poz + 1)
    else pozitiiImpareRec (tail l) (poz + 1)

multDigitsRec :: String -> Int
multDigitsRec str = 
    if null str then 1
    else if isDigit (head str) then digitToInt (head str) * multDigitsRec (tail str)
    else multDigitsRec (tail str)

discountRec :: [Float] -> [Float]
discountRec l = 
    if l == [] then []
    else if (h * 0.75) < 200 then (h * 0.75) : discountRec t
    else discountRec t
    where
        h = head l
        t = tail l 
 
--comprehensiune
semiPareComp :: [Int] -> [Int]
semiPareComp l = [x `div` 2 | x <- l, mod x 2 == 0]

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp x y l = [n | n <- l, x <= n, n <= y]

pozitiveComp :: [Int] -> Int
pozitiveComp l = length [x | x <- l, x > 0]

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [poz | (x, poz) <- zip l [0..(length l - 1)], mod x 2 == 1]

multDigitsComp :: String -> Int
multDigitsComp str = foldr (*) 1 [digitToInt(x) | x <- str, isDigit(x) == True]

discountComp :: [Float] -> [Float]
discountComp l = [x * 0.75 | x <- l, x * 0.75 < 200]

--lab3
--L3.1
--1
factori :: Int -> [Int]
factori n = [x | x <- [1..n], mod n x == 0]

--2
prim :: Int -> Bool 
prim n = length (factori n) == 2 

--3
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], (prim x)]

--L3.2 (zip)
myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 l1 l2 l3 = [(x1, x2, x3) | let m = min (length l1) (min (length l2) (length l3)), (x1, p1) <- zip l1 [0..(m - 1)], (x2, p2) <- zip l1 [0..m], (x3, p3) <- zip l1 [0..m], p1 == p2, p1 == p3 ]

--L3.3 (map)
--1
firstEl :: [(a, b)] -> [a]
firstEl l = map fst [(a, b) | (a, b) <- l]

--2
sumList :: [[Int]] -> [Int]
sumList l = map sum l

--3
prel2 :: [Integer] -> [Integer]
prel2 l = map (`div` 2) [x | x <- l, mod x 2 == 0] ++ map (*2) [y | y <- l, mod y 2 == 1 ] 

--L3.4 (map, filter)
--1
contine :: [String] -> Char -> [String]
contine str c = filter (elem c) str

--2
patrateImpare :: [Int] -> [Int]
patrateImpare l = map (^2) (filter odd l)

--3
patratePozImpare :: [Int] -> [Int]
patratePozImpare l = map (^2) [x | (x, poz) <- zip l [0..(length l - 1)], mod poz 2 == 1 ]

--4
numaiVocale :: [[Char]] -> [[Char]]
numaiVocale l = map (filter (`elem` "aeiouAEIOU")) l

--L3.5
myMap :: (a -> b) -> [a] -> [b]
myMap f (h : t) = 
    if null (h : t) then []
    else f h : myMap f t

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter f (h : t) = 
    if null (h : t) then []
    else if f h then h : myFilter f t
    else myFilter f t


--lab4
--recursie
produsRec :: [Int] -> Int 
produsRec l = 
    if null l then 1
    else (head l) * produsRec (tail l)

andRec :: [Bool ] -> Bool 
andRec l = 
    if null l then True 
    else (head l) && andRec (tail l)

concatRec :: [[a]] -> [a]
concatRec l = 
    if null l then []
    else h ++ concatRec t
    where 
        h = head l
        t = tail l

rmChar :: Char -> String -> String 
rmChar c str = 
    if null str then ""
    else if h == c then rmChar c t
    else h :rmChar c t
    where 
        h = head str
        t = tail str

rmCharsRec :: String -> String -> String 
rmCharsRec str1 str2 = 
    if null str2 then str1
    else rmCharsRec (rmChar h str1) t
    where 
        h = head str2
        t = tail str2

--foldr
produsFold :: [Integer ] -> Integer 
produsFold l = foldr (*) 1 l 

andFold :: [Bool ] -> Bool
andFold l = foldr (&&) True l

concatFold :: [[a]] -> [a]
concatFold l = foldr (++) [] l

rmCharsFold ::  String -> String -> String 
rmCharsFold str1 str2 = foldr rmChar [x | x <- str1] str2

--functii de nivel inalt
--1
ordonataNat :: [Int ] -> Bool 
ordonataNat [] = True 
ordonataNat [x] = True 
ordonataNat l = and [x < y | (x, px) <- zip l [0..(length l - 1)], (y, py) <- zip l [0..(length l - 1)], px < py]

--2
ordonataNat1 :: [Int ] -> Bool 
ordonataNat1 [] = True 
ordonataNat1 [x] = True 
ordonataNat1 [x, y] = 
    if x < y then True 
    else False 
ordonataNat1 (x:xs:xxs) = 
    if x < xs then True && ordonataNat1 xxs
    else False

--3
ordonare :: Int -> Int -> Bool
ordonare a b
    | a < b = True
    | otherwise = False

divizibilitate :: Int -> Int -> Bool
divizibilitate a b
    | b `mod` a == 0 = True
    | otherwise = False

lexicografic :: [Char] -> [Char] -> Bool
lexicografic a b
    | a < b = True
    | otherwise = False

ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata l f = and [f (fst x) (snd x) | x <- zip l (tail l)] 

--lab5
--universalitatea functiei foldr
sumaPatrateImpareFold :: [Integer ] -> Integer 
sumaPatrateImpareFold l = foldr (+) 0 [x ^2 | x <- l]

--1
semnRec :: [Integer ] -> String 
semnRec l = 
    if null l then ""
    else if h == 0 then '0' : semnRec t
    else if -9 <= h && h < 0 then '-' : semnRec t 
    else if  0 < h && h < 9 then '+' : semnRec t
    else semnRec t
    where 
        h = head l
        t = tail l

semn :: Integer -> String  
semn i = 
    if i == 0 then "0"
    else if i <= -9 && i < 0 then "-"
    else if 0 < i && i <= 9 then  "+"
    else ""
semnFold :: [Integer ] -> String  
semnFold l =  foldr (++) "" [(semn x) | x <- l]

--matrici
--1
corect :: [[a]] -> Bool 
corect m = foldr (&&) True [l1 == l2 | i <-[0..(length m - 2)], let l1 = length (m !! i), let l2 = length (m !! (i + 1))]

 --2
el :: [[a]] -> Int -> Int -> a
el m i j = (m !! i) !! j

--3
transforma :: [[a]] -> [(a, Int, Int)]
transforma m = [((m !! i) !! j, i, j) | i <- [0..(length m) - 1], j <- [0..(length (m !! i) - 1)]]


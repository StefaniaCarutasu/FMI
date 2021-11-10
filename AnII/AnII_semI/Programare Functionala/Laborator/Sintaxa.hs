{- comentariu
pe mai 
multe linii-}

maxInt :: Int
maxInt = maxBound :: Int --maxInt
minInt = minBound :: Int --minInt
x :: Char
x = 'a'

sumOfNums = sum [1, 2, 10] --suma elementelor din lista

modEx = mod 5 4 --operator infix face restul
modEx1 = 5 `mod` 4

rad = sqrt (fromIntegral 9) --sqrt se poate aplica doar pe float si asa se face conversia

pival = pi --pi
pow9 = exp 9

squared9 = 9 ** 2 --patratul unui nr

primeNumbers = [3, 5, 7, 11]

morePrime = primeNumbers ++ [13, 17, 19] --concatenare liste

numere = 2 : 7 : 9 : 0 : 100 : []  --formare unei liste

morePrime2 = 2 : morePrime  --push front in lista

lenPrime = length morePrime2    --lungimea unei liste

revPrime = reverse morePrime2   --inversarea unei liste

isListEmpty = null morePrime2   --verifica daca lista este goala

secondPrime = morePrime2 !! 1   --elementul de pe pozitia 1 echivalent cu [1]

first3Primes = take 3 morePrime2    --lista formata din primele 3 el din lista mare

removePrimes = drop 3 morePrime2    --lista fara primele 3 elemente

is7 = 7 `elem` morePrime2   --verifica daca un el este in lista

is10 = elem 10 morePrime2

maxPrime = maximum morePrime2   --maximul din lista

newList = 2 : 3 : 5 : []

prodPrimes = product newList    --produsul elementelor din lista
sumPrimes = sum newList     --suma el din lista

zeroToTen = [0..10]     --lista nr de la 0 la 10

evenList = [2, 4..20]   --lista doar de nr pare

letterList = ['A', 'C'..'Z']    --imi va intoarce un cuv format din toate literele una da una ba

letterList2 = ['a'..'z']

infinPow10 = [10, 20..]

many2s = take 10 (repeat 2)     --face o lista din 10 de 2
--similar avem
many3s = replicate 10 3

cycleList = take 13 (cycle [1,2,3,4,5])     --primele 13 elemente din repetarea listei

listTimes2 = [x*2 | x <- [1..10]]   --[2,4,6,8,10,12,14,16,18,20]

listTimes3 = [x*3 | x <- [1..20], x*3 <= 50]    --[3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48]

divBy9n13 = [x | x <- [1..500], mod x 13 == 0, mod x 9 == 0]    --[117,234,351,468]
 
--sortedList = sort [9, 8, 7, 6]

sumOfLists = zipWith (+) [1, 2, 3, 4, 5] [6,7,8,9,10]   --aduna element cu element

listBiggerThan5 = filter (>5) morePrime2    --ia el >5 din lista

evensUpTo20 = takeWhile (<= 20) [2, 4..]    --simuleaza un while, creeaza lista cu el pare pana la 20

multOfList = foldr (*) 1 [2,3,4,5]  --inmulteste toate el intre ele din lista

pow3List = [3^n | n<- [1..10]]  --vector cu 3 la puterea n

pow3 = [n^3 | n <- [1, 3..9]]   --vector de n la puterea 3

y = pow3 !! 0   --pow3[0]

multiTable = [[x*y | y <- [1..10]] | x <- [1..10]]  --matrice cred?

randTuple = (1, "Random Tuple")

bobSmith = ("Bob Smith")

{-bobsName = fst bobSmith     --primul elem din tuplu

bobsAge = snd bobSmith  --ultimul elem din tuplu-}

names = ["Bob", "Mary", "Tom"]
addresses = ["123 Main", "234 North", "567 South"]

nameNAdress = zip names addresses

main = do
    putStrLn "What's your name"     --cout
    name <- getLine     --cin
    putStrLn ("Hello " ++ name)

addMe :: Int -> Int -> Int  --tipul de date
--funcName param1 param 2 = operations (returned value)
addMe x y = x + y

sumMe x y = x + y

addTuples :: (Int, Int) -> (Int, Int) -> (Int, Int)
addTuples (x, y) (x2, y2) = (x + x2, y + y2)

whatAge :: Int -> String
whatAge 16 = "You can drive"
whatAge 18 = "You can vote"
whatAge 21 = "You can drink" 
whatAge _ = "Nothing important"

factorial :: Int -> Int --recursie
factorial 0 = 1
factorial n = n * factorial (n-1)

prodFact n = product [1..n]

isOdd :: Int -> Bool

isOdd n
    | mod n 2 == 0 = False
    | otherwise = True

isEven n = mod n 2 == 0

whatGrade :: Int -> String
whatGrade age 
    |(age >= 5) && (age <= 6) = "Kindergarten"
    |(age > 6) && (age <= 10) = "Elementary School"
    |(age > 10) && (age <= 14) = "Middle School"
    |(age > 14) && (age <= 18) = "High School"
    | otherwise = "Go to college"

batAvgRating :: Double -> Double -> String
batAvgRating hits atBats
    |avg <= 0.200 = "Terrible"
    |avg <= 0.250 = "Average"
    |avg <= 0.280 = "Pretty good"
    |otherwise = "Superstar"
    where avg = hits / atBats

getListItems :: [Int] -> String
getListItems [] = "Empty"
getListItems (x:[]) = "Your list starts with " ++ show x
getListItems (x:y:[]) = "Your list contains " ++ show x ++ " and " ++ show y
getListItems (x:xs) = "The first item is " ++ show x ++ "and the rest are " ++ show xs

{-getFirstItem :: String -> String
getFirstItem [] = "Empty"
getFirstItem all@(x:xs) = "The first letter in " ++ all ++ "is" ++ x-}

times4 :: Int -> Int
times4 x = x*4

listTimes4 = map times4 [1,2,3,4,5]
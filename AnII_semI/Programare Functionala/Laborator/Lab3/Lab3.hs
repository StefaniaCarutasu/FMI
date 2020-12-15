factori :: Int -> [Int]
factori n = [x | x<- [2..div n 2], mod n x == 0]

prim :: Int -> Bool
prim n =
    if null (factori n) then True
    else False

prim2 ::Int -> Bool
prim2 x = length(factori x) == 0

numerePrime :: Int -> [Int]
numerePrime n = [x | x <-[1..n], prim x]

lista = [(x,y)| x <- [1..3], y <- [1..5]]

myZip3 :: [Int] -> [Int] -> [Int] -> [[Int]]
myZip3 list1 list2 list3 = 
    if null list1 || null list2 || null list3 then []
    else [head list1, head list2, head list3]: myZip3 (tail list1) (tail list2) (tail list3)

l = map (1 `elem`) [[2,3],[1,2]]

firstEl :: [(a,b)] -> [a]
firstEl list = map (fst) list
suma :: [Int] -> Int
suma lista = 
    if null lista then 0
    else head lista + suma (tail lista)
sumtList :: [[Int]] -> [Int]
sumtList lista = map suma lista

prel2 :: [Int] -> [Int]
prel2 list= 
    if even (head list) then (head list) `div` 2 : prel2 (tail list)
    else head list * 2 : prel2 (tail list)

--1
isElem :: Char -> [String]->[String]
isElem c lista = filter (c `elem`) lista

--2
patrateImpare :: [Int] -> [Int]
patrateImpare lista = filter odd [x^2 | x <- lista]

--3
patratePozImpare :: [Integer] -> [Integer]
patratePozImpare l = map (^2) [fst x | x <- zip l [0..], snd x `mod` 2 == 1]
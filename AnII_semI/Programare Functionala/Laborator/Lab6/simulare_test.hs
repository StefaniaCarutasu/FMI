--1
--a
import Data.Char 
f :: Char -> Bool
f c = 
    if c `elem` "ABCDEFGHIJKLMabcdefghijklm" then True
    else if c `elem` "NOPQRSTUVWXYZnopqrstuvwxyz" then False
    else error "Nu este in alfabet"

--b
g :: String -> Bool
g str = length([x | x <- str, isAlpha x == True, f(x) == True]) > length([x | x <- str, isAlpha x == True, f(x) == False])

--c
h :: String -> Bool
h str = h1 str > h2 str 
h1 :: String -> Int
h1 str = 
    if null str then 0
    else if isAlpha(head str) && f(head str) == True then 1 + h1(tail str)
    else h1(tail str)
h2 :: [Char] -> Int
h2 str = 
    if null str then 0
    else if isAlpha(head str) && f(head str) == False then 1 + h1(tail str)
    else h1(tail str)


--2
--a
c :: [Int] -> [Int]
c list = [list !! i | i <- [0..(length(list)-2)], list !! i == list !! (i+1) ]

--b
d :: [Int] -> [Int]
d list = 
    if null list then []
    else if length list == 1 then []
    else if head list == head(tail list) then head list : d(tail list)
    else d(tail list)

--c
prop_cd :: [Int] -> Bool
prop_cd list = c list == d list 

x :: Bool
x = prop_cd [3,1,1,3,3,5] == True
y :: Bool
y = prop_cd [2,1,4,1,2] == True
z :: Bool
z = prop_cd [7] == True
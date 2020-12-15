import Data.Char
import Data.List
--1
--folosesc functia reverse ce imi inverseaza ordinea literelor din fiecare cuvant
-- apoi verific daca un cuvant este egal cu inversul lui si functia returneaza true
csPalindromRec :: [String] -> Bool
csPalindromRec ls =
    if null ls then False 
    else if (head ls) == reverse (head ls) then True 
    else csPalindromRec (tail ls)


--2
csPalindrom :: [String] -> Bool
csPalindrom ls = length [x | x <- ls, x == reverse x] > 0

--3
--folosesc functia ajutatoare csEPalindrom pentru e filtra forma o lista doar din cuvinte palindrom
csEPalindrom :: String -> Bool
csEPalindrom str = 
    if str == reverse str then True
    else False
csPalindromFilter :: [String] -> Bool
csPalindromFilter ls = length (filter csEPalindrom ls) > 0

--4
cs_test_palindrom :: [String] -> Bool
cs_test_palindrom ls = csPalindromRec ls == csPalindromFilter ls


csNrAparitiiZero :: [Int] -> Int
csNrAparitiiZero list = length [x | x <- list, x == 0]

csAparitii :: [Int] -> Int
csAparitii l = length [l !! i | i <- [1..(length l - 2)], ((l !! i) == 0 && (l !! (i + 1) == 1) || (l !! i) == 0 && (l !! (i - 1) == 1)) ]

csTransforma :: [Int] -> [Int]
csTransforma l = 
    if null l then []
    else if length l == 1 then l
    else if head l == 0 && (head (tail l) == 1 || head (tail l) == 0) then csTransforma (tail l)
    else if head l == 1 && (head (tail l) == 0) then (head l) : csTransforma (tail (tail l))
    else head l : csTransforma (tail l)
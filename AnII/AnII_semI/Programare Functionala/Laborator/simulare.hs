--a
import Data.Char
primaJumatate ::  Char -> Bool
primaJumatate c = 
    if (c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M') then True
    else if (c > 'm' && c <= 'z') || (c > 'M' && c <= 'Z') then False
    else error "Nu este litera din alfabet"
--b
maiMultePrimaJumatate :: String -> Bool
maiMultePrimaJumatate str = length[x | x <- str, isAlpha x == True, primaJumatate x == True] > length [x | x <- str, isAlpha x == True, primaJumatate x == False]

--c
numaraCifre :: String -> Int
numaraCifre str = 
    if null str then 0
    else if isAlpha h && primaJumatate h == True then 1 + numaraCifre t 
    else if isAlpha h && primaJumatate h == False then (-1) + numaraCifre t
    else numaraCifre t
    where
        h = head str 
        t = tail str 
maiMulteRec :: String -> Bool
maiMulteRec str = numaraCifre str > 0

--2
--a
succesiv :: [Int] -> [Int]
succesiv l = [l !! i | i <- [0..(length l -2)], l !! i == l !! (i + 1)]

--b
succesivRec :: [Int] -> [Int]
succesivRec l = 
    if null l then []
    else if length l == 1 then []
    else if head l == head (tail l) then head l : succesivRec (tail l)
    else succesivRec (tail l)

--c
test_succesiv :: [Int] -> Bool
test_succesiv l = succesivRec l == succesiv l
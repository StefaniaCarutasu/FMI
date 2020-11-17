import Data.Char
import Data.List
--L2.3
--descrieri de liste
pozitiveComp :: [Int] -> Int
pozitiveComp lista = length [x | x <- lista, x > 0]

--recursie 
pozitiveRec :: [Int] -> Int
pozitiveRec lista = 
    if null lista then 0
    else if head lista > 0 then 1 + pozitiveRec (tail lista)
    else pozitiveRec (tail lista)

--L2.5
--recursie
multDigitsRec :: String -> Int
multDigitsRec sirCaractere =
    if length sirCaractere == 0 then 1
    else if isDigit (head sirCaractere) then (digitToInt (head sirCaractere)) * multDigitsRec (tail sirCaractere)
    else multDigitsRec (tail sirCaractere)

--descrieri liste
multDigitsComp :: String -> Int
multDigitsComp sirCaractere = product [digitToInt x | x <-sirCaractere, isDigit x == True]

--L2.6
--descrieri de liste
discountComp :: [Float] -> [Float]
discountComp lista = [x - 25/100 *x | x <- lista, x - 25/100 * x < 200]

--recursie 
discountRec :: [Float] -> [Float]
discountRec lista =
    if null lista then []
    else if (head lista) - 25/100 * (head lista) < 200 then (head lista) - 25/100 * (head lista) : discountRec (tail lista)
    else discountRec (tail lista)
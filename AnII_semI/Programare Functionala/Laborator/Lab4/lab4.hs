import Numeric.Natural
--I
--Ex1
--recursie
produsRec :: [Integer] -> Integer
produsRec l = 
  if null l then 1
  else head l * produsRec (tail l)

--foldr
produsFold :: [Integer] -> Integer
produsFold l = foldr (*) 1 l

--Ex2
--recursie
andRec :: [Bool] -> Bool
andRec l = 
  if null l then True
  else if head l == True then (head l) && andRec (tail l)
  else False

--foldr
andFold :: [Bool] -> Bool
andFold l = foldr (&&) True l

--Ex3
--recursie
concatRec :: [[a]] -> [a]
concatRec l = 
  if null l then []
  else head l ++ concatRec (tail l)

--foldr
concatFold :: [[a]] -> [a]
concatFold l = foldr (++) [] l

--Ex4
--a
rmChar :: Char -> String -> String
rmChar c s = 
  if null s then []
  else if (head s) == c then rmChar c (tail s)
  else (head s) :rmChar c (tail s)

--b
rmCharsRec :: String -> String -> String
rmCharsRec s1 s2 = 
  if null s1 then s2
  else rmCharsRec (tail s1) (rmChar (head s1) s2)

test_rmchars :: Bool
test_rmchars = rmCharsRec ['a'..'l'] "fotbal" == "ot"

--c
rmCharsFold :: String -> String -> String
rmCharsFold s1 s2 = foldr rmChar s2 s1

--II

logistic :: Num a => a -> a -> Natural -> a
logistic rate start = f
  where
    f 0 = start
    f n = rate * f (n - 1) * (1 - f (n - 1))

logistic0 :: Fractional a => Natural -> a
logistic0 = logistic 3.741 0.00079

ex1 :: Natural
ex1 = 7


ex20 :: Fractional a => [a]
ex20 = [1, logistic0 ex1, 3]

ex21 :: Fractional a => a
ex21 = head ex20

ex22 :: Fractional a => a
ex22 = ex20 !! 2

ex23 :: Fractional a => [a]
ex23 = drop 2 ex20

ex24 :: Fractional a => [a]
ex24 = tail ex20


ex31 :: Natural -> Bool
ex31 x = x < 7 || logistic0 (ex1 + x) > 2

ex32 :: Natural -> Bool
ex32 x = logistic0 (ex1 + x) > 2 || x < 7
ex33 :: Bool
ex33 = ex31 5

ex34 :: Bool
ex34 = ex31 7

ex35 :: Bool
ex35 = ex32 5

ex36 :: Bool
ex36 = ex32 7

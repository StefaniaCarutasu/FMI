-- 1
import Test.QuickCheck
import Data.List
import Data.Char

-- 2
double :: Int -> Int
double = (* 2)

triple :: Int -> Int
triple = (* 3)

penta :: Int -> Int
penta = (* 5)

-- 3
test x = (double x + triple x) == (penta x)

-- 4

-- 5
{-
*Main> quickCheck test
+++ OK, passed 100 tests.
-}

-- 6
testW x = (double x - penta x) == (triple x)

-- 7
myLookUp :: Int -> [(Int, String)] -> Maybe String
myLookUp nr [] = Nothing
myLookUp nr (x : xs)
     | fst x == nr = Just (snd x)
     | otherwise = myLookUp nr xs

testLookUp :: Int -> [(Int, String)] -> Bool
testLookUp nr list = myLookUp nr list == lookup nr list

-- Constrangeri
testLookUpCond :: Int -> [(Int,String)] -> Property
testLookUpCond n list = n > 0 && n `div` 5 == 0 ==> testLookUp n list

-- 8
myLookUp' :: Int -> [(Int, String)] -> Maybe String
myLookUp' nr [] = Nothing
myLookUp' nr ((n, (y : ys)) : xs)
     | n == nr = Just ((toUpper y) : ys)
     | otherwise = myLookUp' nr xs
testLookUp' :: Int -> [(Int, String)] -> Bool
testLookUp' nr list = undefined

-- Tipuri algebrice
-- 9
data ElemIS = I Int | S String
     deriving (Show,Eq)



myLookUpElem :: Int -> [(Int,ElemIS)]-> Maybe ElemIS
myLookUpElemnr [] = Nothing
myLookUpElem nr (x : xs)
     | fst x == nr = Just (snd x)
     | otherwise = myLookUpElem nr xs

testLookUpElem :: Int -> [(Int,ElemIS)] -> Bool
testLookUpElem nr list = myLookUpElem nr list == lookup nr list
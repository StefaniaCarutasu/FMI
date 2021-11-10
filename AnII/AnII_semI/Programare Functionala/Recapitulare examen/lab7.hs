import Test.QuickCheck
import Data.Maybe
import Data.List
import Data.Char
import System.Random


--2
double :: Int -> Int
double x = 2 * x
triple :: Int -> Int
triple x = 3 * x
penta :: Int -> Int
penta x = 5 * x

test x = (double x + triple x) > (penta x)

--7
myLookUp :: Int -> [(Int, String)] -> Maybe String
myLookUp i list = 
    if null list then Nothing 
    else if fst h == i then Just (snd h)
    else myLookUp i t
    where
        h = head list
        t = tail list

testLookUp ::  Int -> [(Int, String)] -> Bool
testLookUp i list = myLookUp i list == lookup i list

testLookUpCond :: Int -> [(Int,String)] -> Property
testLookUpCond n list = n > 0 && n `div` 5 == 0 ==> testLookUp n list

--8
myLookUp' :: Int -> [(Int, String)] -> Maybe String
myLookUp' nr [] = Nothing
myLookUp' nr ((n, (y : ys)) : xs)
     | n == nr = Just ((toUpper y) : ys)
     | otherwise = myLookUp' nr xs

isUpperList ::  [(Int, String)] -> Bool
isUpperList list = 
    if null list then True
    else if isUpper ((snd h) !! 0) == False then False
    else isUpperList t
    where 
        h = head list
        t = tail list

--9
data ElemIS = I Int | S String 
    deriving (Show, Eq)

instance Arbitrary ElemIS where
     arbitrary = elements ((I (fst $ random (mkStdGen 1) :: Int)) : 
               [(S (take (fst $ random (mkStdGen 1) :: Int) (randomRs ('A' , 'z') (mkStdGen 1) :: [Char])))])

myLookUpElem :: Int -> [(Int , ElemIS)] -> Maybe ElemIS
myLookUpElem i list = 
    if null list then Nothing 
    else if fst h == i then Just (snd h)
    else myLookUpElem i t
    where 
        h = head list
        t = tail list

testLookUpElem ::  Int -> [(Int , ElemIS)] -> Bool 
testLookUpElem i list = myLookUpElem i list == lookup i list



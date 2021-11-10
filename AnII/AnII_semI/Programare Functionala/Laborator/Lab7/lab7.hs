import Test.QuickCheck

double ::Int->Int
double=undefined
triple ::Int->Int
triple = undefined
penta :: Int -> Int
penta = undefined

test x = (double x + triple x) == (penta x)
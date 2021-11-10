fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n <2 = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)

fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n = 
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)

semiPareRecDestr :: [Int] -> [Int]
semiPareRecDestr  l 
    | null l = l 
    | even h = div h 2 : t' 
    | otherwise = t' 
    where
        h = head l
        t = tail l
        t' = semiPareRecDestr t 

intervalRec :: Int -> Int -> [Int] -> [Int]
intervalRec lo hi (h:t)
    | lo <= h && h <= hi = h: (intervalRec lo hi t)
    | otherwise = intervalRec lo hi t 

--L2.4
{-pozCurenta :: [Int] -> [(Int, Int)] 
pozCurenta l = zip [0..] l
pozitiiImpareRec :: [(Int, Int)] -> [Int]
pozitiiImpareRec (pozCurenta l)
    | null l = []
    | odd snd h = fst h : t'
    | otherwise = t'
    where
        h = head -}

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [fst(x) | x <- zip [0..] l, snd(x) `mod` 2 == 1]
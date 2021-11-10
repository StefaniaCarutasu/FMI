
--L3.4
--3
patratePozImpare :: [Int] -> [Int]
patratePozImpare l = map (^2) [fst x | x <- zip l [0..], odd (snd x)]

--4
numaiVocale :: [[Char]] -> [[Char]]
numaiVocale l = map (filter (`elem` "aeiouAEIOU")) l

--L3.5
myMap :: (a -> b) -> [a] -> [b]
myMap f (h : t) = 
    if null (h : t) then []
    else f h : myMap f t

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter f (h : t) = 
    if null (h : t) then []
    else if f h then h : myFilter f t
    else myFilter f t
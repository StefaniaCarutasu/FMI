--Universalitatea functiei foldr
--Ex1
--recursie
intoarceSemn :: Integer -> Char
intoarceSemn i =
    if i == 0 then '0'
    else if i > 0 then '+'
    else '-'
semn :: [Integer] -> String
semn l = 
    if null l then []
    else if -9 <= h && h <= 9 then intoarceSemn h : semn t
    else semn t
    where
        h = head l
        t = tail l 

test_semn :: Bool
test_semn = semn[5,10,-5,0]=="+-0"

--foldr
semnFold :: [Integer] -> String
semnFold l = foldr (:) [] [x| x <- (map intoarceSemn [y| y <- l, y < 10, y > -10])]
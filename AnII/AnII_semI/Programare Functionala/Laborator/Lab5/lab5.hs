--Ex1
corect :: [[a]] -> Bool
corect l = 
    if null l then True
    else if length l == 1 then True
    else length( head l) == length (head (tail l)) && corect(tail l)

corect1:: [[a]] -> Bool
corect1 l = foldr (&&) True [length (l !! i) == length (l !! (i-1))| i<- [1..((length l) - 1)]]

--Ex2
el :: [[a]] -> Int -> Int -> a
el l i j = (l !! i) !! j

--Ex3
transforma :: [[a]] -> [(a, Int, Int)]
transforma l = [(el l i j, i, j)| i <- [0..(length l - 1)], j <- [0..(length (l !! i) - 1)]]

enumera :: [a] -> [(a, Int)]
enumera list = zip list [0..]



insereazaPozitie :: ([(a, Int)], Int) -> [(a, Int, Int)]
insereazaPozitie (lista, linie) =
map (\(x, coloana) -> (x, linie, coloana)) lista



transforma :: [[a]] -> [(a, Int, Int)]
transforma matrix = concat (map insereazaPozitie (enumera (map enumera matrix)))

          
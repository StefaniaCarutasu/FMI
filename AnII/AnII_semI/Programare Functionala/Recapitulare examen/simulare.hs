import Data.List
data Arbore a
    = Nod (Arbore a) a (Arbore a)
    | Frunza a | Vid 

--a
fArbToList :: (Arbore a) -> [a]
fArbToList Vid = []
fArbToList (Frunza x) = [x]
fArbToList (Nod l x r) = (fArbToList l) ++ [x] ++ (fArbToList r)

fFaraDuplicate :: Eq a => (Arbore a) -> Bool
fFaraDuplicate arb = length (fArbToList arb) == length (nub (fArbToList arb))

fVerif :: Ord a => [a] -> Bool 
fVerif (x : []) = True 
fVerif (x : xx : []) = x < xx
fVerif (x : xx : xxx) = x < xx && fVerif (xx : xxx)

fEArbore :: Ord a => (Arbore a) -> Bool
fEArbore arb = fFaraDuplicate arb && fVerif (fArbToList arb) 

--b
inserareArbore :: Ord a => (Arbore a) -> a -> (Arbore a)
inserareArbore Vid elem = (Nod Vid elem Vid)
inserareArbore (Frunza x) elem = 
    if x < elem then (Nod Vid x (Nod Vid elem Vid))
    else (Nod (Nod Vid elem Vid) x Vid )
inserareArbore (Nod l x r) elem = 
    if x < elem then (Nod (inserareArbore l x) elem r)
    else (Nod l elem (inserareArbore r x))

--c
instance Functor Arbore where
    fmap f Vid = Vid
    fmap f (Frunza x) = Frunza (f x)
    fmap f (Nod l x r) = Nod (fmap f l) (f x) (fmap f r)

--2
--a
foldArb :: (a -> b -> b) -> b -> Arbore a -> b
foldArb f i Vid = i
foldArb f i (Frunza x) = f x i 
foldArb f i (Nod l x r) = foldr f (f x (foldr f i l)) r 

instance Foldable Arbore where
    foldr = foldArb

--b
instance Show a => Show (Arbore a) where
    show Vid = ""
    show (Frunza x) = show x
    show (Nod l x r) = show r ++ ", " ++ ", "  ++ show x ++ ", " ++ show l
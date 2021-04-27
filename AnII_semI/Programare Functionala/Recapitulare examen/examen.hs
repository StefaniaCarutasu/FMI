import Data.String
import Prelude hiding (lookup)
import qualified Data.List as List

type Id = String 
type Link = Maybe String
type Info = Int 
data Node = Node Id Info Link
            deriving Show

data NodeSpace = NodeSpace [Node]
            deriving Show 

--a
stSuccesor :: NodeSpace -> Node -> Maybe Id
stSuccesor (NodeSpace []) _ = Nothing
stSuccesor list (Node _ _ Nothing) = Nothing  
stSuccesor (NodeSpace ((Node id _ _) : t) (Node idCaut info (Just idLink)) = 
    if id == idCaut then Just idLink
    else stSuccesor (NodeSpace t) (Node idCaut info (Just idLink))

stLista :: NodeSpace
stLista = NodeSpace [Node "a" 1 Nothing, Node "b" 2 (Just "a"), Node "b" 1 (Just "a")]

stTestSuccesor :: NodeSpace -> Node -> Bool 
stTestSuccesor stLista (Node "b" 2 (Just "a")) = stSuccesor stLista (Node "b" 2 (Just "a")) == Just "a"
--b
stEgal :: Node -> Int
stEgal (Node id info link) = info

instance Eq Node where
    x == y = (stEgal x) == (stEgal y)
    x /= y = (stEgal x) /= (stEgal y)

--vreau sa verific daca NodeSpace contine Node si parcurg toata
--lista de Node continuta de NodeSpace pana la final
--Daca am gasit nodul returnez True
--Daca am ajuns la finalul listei returnez False
stContine :: NodeSpace -> Node -> Bool 
stContine (NodeSpace l) (Node id info link) =
    if length l == 0 then False
    else if h == (Node id info link) then True 
    else stContine (NodeSpace t) (Node id info link)
    where 
        h = head l
        t = tail l

stListeEgale :: NodeSpace -> NodeSpace -> Bool 
stListeEgale (NodeSpace l1) (NodeSpace l2) = 
    if length l1 == 0 then True
    else if stContine (NodeSpace l2) h then False
    else stListeEgale (NodeSpace t) (NodeSpace l2)
    where 
        h = head l1
        t = tail l1

instance Eq NodeSpace where
    x == y = stListeEgale x y
    x /= y = stListeEgale x y

--c
type MGraph = [(Id, [(Info, Id)])]


--2
data B e = R e Int | B e ::: B e
        deriving Eq 
infixr 5 :::

--c
stFoldB :: (a -> b -> b) -> b -> B a -> b
stFoldB f i (R a _) = f a i
stFoldB f i ((R a _) ::: t) = f a (foldr f i t)

instance Foldable B where
    foldr = stFoldB

--d
class C e where
    cFilter :: (a -> Bool) -> e a -> e (Maybe a)
    fromList :: [a] -> e a

instance C B where
    cFilter f (R el i) = 
        if f el then (R (Just el) i)
        else (R Nothing i)
    fromList (h:t) = (R h i) ::: fromList t
                    where 
                        i = length t + 1


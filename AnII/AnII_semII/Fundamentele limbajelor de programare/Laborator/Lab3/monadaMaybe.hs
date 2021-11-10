{- 
Monada Maybe este definita in GHC.Base 

instance Monad Maybe where
  return = Just
  Just va  >>= k   = k va
  Nothing >>= _   = Nothing

instance Applicative Maybe where
  pure = return
  mf <*> ma = do
    f <- mf
    va <- ma
    return (f va)       

instance Functor Maybe where              
  fmap f ma = pure f <*> ma   
-}

--1.1
(<=<) :: (a -> Maybe b) -> (c -> Maybe a) -> c -> Maybe b
f <=< g = \x -> g x >>= f

--1.2
asoc :: (Int -> Maybe Int) -> (Int -> Maybe Int) -> (Int -> Maybe Int) -> Int -> Bool
asoc f g h x = (h <=< g <=< f $ x) == ((h <=< g) <=< f $x)

--2 
pos :: Int -> Bool
pos x = (x >= 0)

foo :: Maybe Int -> Maybe Bool
foo mx = mx >>= (Just . pos)

--2.1
--Functia foo ia pe x in monada mx folosind lambda expresia si dupa aplica lui x functia pos si intoarce just pos x

--2.2
foo2 :: Maybe Int -> Maybe Bool
foo2 mx = do
    pos <$> mx

--3
addM :: Maybe Int -> Maybe Int -> Maybe Int
addM _ Nothing = Nothing
addM Nothing _ = Nothing
addM mx my = do
    x <- mx
    y <- my
    return (x + y)

addM2 :: Maybe Int -> Maybe Int -> Maybe Int
addM2 _ Nothing = Nothing
addM2 Nothing _ = Nothing
addM2 mx my = mx >>= (\x -> my >>= \y -> return (x + y))

--Notatia do si secventiere
--4
cartesian_product :: Monad m => m a -> m b -> m (a, b)
cartesian_product xs ys = xs >>= (\x -> ys >>= \y -> return (x, y))

cartersianProduct :: Monad m => m a -> m b -> m (a, b)
cartersianProduct xs ys = do
    x <- xs
    y <- ys
    return (x, y)


--prod f xs ys - [f x y | xs, y <- ys]
prod :: Monad m => (t1 -> t2 -> b) -> m t1 -> m t2 -> m b
prod f xs ys = do
    x <- xs
    y <- ys
    return (f x y)

myGetLine :: IO String 
myGetLine = getChar >>= \x -> 
    if x == '\n' then return []
    else myGetLine >>= \xs -> return (x:xs)

--5
prelNo :: Floating a => a -> a
prelNo noin = sqrt noin 
ioNumber = do 
    noin <- readLn :: IO Float 
    putStrLn $ "Intrare\n" ++ (show noin)
    let noout = prelNo noin 
    putStrLn  $ "Iesire"
    print noout

ioNumber2 = (readLn :: IO Float) >>= (\noin -> (putStrLn $ ("Intrare\n" ++ (show noin))) >> (putStrLn $ "Iesire") >> print (prelNo noin))


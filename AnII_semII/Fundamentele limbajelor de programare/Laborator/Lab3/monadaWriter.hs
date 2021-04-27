{-
--- Monada Writer
newtype WriterS a = Writer { runWriter :: (a, String) } 
    deriving(Show)

instance  Monad WriterS where
  return va = Writer (va, "")
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)

instance  Applicative WriterS where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor WriterS where              
  fmap f ma = pure f <*> ma     


tell :: String -> WriterS () 
tell log = Writer ((), log)

--1.1

logIncrement :: Int -> WriterS Int
logIncrement x = do
    tell("increment: " ++ show x ++ "\n")
    return (x + 1)

logIncrement2 :: Int -> WriterS Int 
logIncrement2 x = do
    y <- logIncrement x
    logIncrement y

--1.2
logIncrementn :: Int -> Int -> WriterS Int 
logIncrementn x n = do 
                        if n > 0
                            then do 
                                y <- logIncrement x
                                logIncrementn y (n - 1)
                        else do
                            return x

-}

-- 2
newtype WriterLS a = Writer { runWriter :: (a, [String]) } 
instance  Monad WriterLS where
  return va = Writer (va, [])
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)

instance  Applicative WriterLS where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor WriterLS where              
  fmap f ma = pure f <*> ma 


tell :: String -> WriterLS () 
tell log = Writer ((), [log])

  
logIncrement :: Int  -> WriterLS Int
logIncrement x = do
                  tell ("increment: " ++ show x)
                  return (x + 1)

logIncrementN :: Int -> Int -> WriterLS Int
logIncrementN x n = do
                      if n > 0 
                        then do
                          y <- logIncrement x
                          logIncrementN y (n - 1)
                        else do
                          return x

-- 3                       
isPos :: Int -> WriterLS Bool
isPos x = if (x>= 0) then (Writer (True, ["poz"])) else (Writer (False, ["neg"])) 

--4
mapWriterLS :: (a -> WriterLS b) -> [a] -> WriterLS [b]
mapWriterLS f xs = let
                     rez = map runWriter (map f xs)
                   in
                     Writer ([x | (x, _) <- rez], [log | (_, [log]) <- rez])

{-
--5
isPos :: Int -> WriterS Bool 
isPos x = 
    if x >= 0 then Writer (True, "poz")
    else Writer (False , "neg")
    
mapWriterS :: (a -> WriterS b) -> [a] -> WriterS [b]
mapWriterS f xs = let
                     rez = map runWriter (map f xs)
                   in
                     Writer ([x | (x, _) <- rez], concat [log ++ "\n" | (_, log) <- rez])
-}



--- Monada State

newtype State state a = State { runState :: state -> (a , state) }

instance Monad (State state) where
    return va = State (\s -> (va , s))
    ma >>= k = State $ \s -> let (va, news) = runState ma s
                             in runState (k va) news

instance Applicative (State state) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)

instance Functor (State state) where
  fmap f ma = pure f <*> ma


-- obtinere starea curenta
get :: State state state
get = State (\s -> (s, s))

-- setare starea curenta
set :: state -> State state ()
set s = State (const ((), s))
-- State(\_ -> ((), s))

-- modificare stare
modify :: (state -> state) -> State state ()
modify f = State (\s -> ((), f s))


-- State Person String
data Person = Person { name :: String, age :: Int }

instance Show Person where
    show (Person name age) = "Person " ++ name ++ " " ++ show age

showPersonN :: Person -> (String, Person)
showPersonN (Person name age) = ("NAME:" ++ name, Person name age)

showPersonA :: Person -> (String, Person)
showPersonA (Person name age) = ("AGE:" ++ show age, Person name age)

showPerson :: Person -> (String, Person)
showPerson pers = let
                    (name, _) = showPersonN pers
                    (age, _) = showPersonA pers
                  in
                    ("(" ++ name ++ ", " ++ age ++ ")", pers)

mshowPersonN :: State Person String
mshowPersonN = State $ showPersonN >>= \name -> return name

mshowPersonA :: State Person String
mshowPersonA = State $ showPersonA >>= \age -> return age

mshowPerson :: State Person String
mshowPerson = State $ showPerson >>= \pers -> return pers
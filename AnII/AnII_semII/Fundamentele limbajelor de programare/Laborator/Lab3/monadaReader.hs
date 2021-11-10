import Data.Char
import Data.String
--- Monada Reader

newtype Reader env a = Reader { runReader :: env -> a }

instance Monad (Reader env) where
  return x = Reader (\_ -> x)
  ma >>= k = Reader f
    where f env = let a = runReader ma env
                  in  runReader (k a) env

instance Applicative (Reader env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)

instance Functor (Reader env) where
  fmap f ma = pure f <*> ma

-- inspecteaza starea curenta
ask :: Reader env env
ask = Reader id

-- modifica  starea doar pt computatia data
local :: (r -> r) -> Reader r a -> Reader r a
local f ma = Reader $ (\r -> (runReader ma)(f r))

--1
data Person = Person {name :: String, age :: Int }

--1.1
showPersonN :: Person -> String 
showPersonN (Person name age) =  "NAME: " ++ name

showPersonA :: Person -> String 
showPersonA (Person name age) = "Age: " ++ show age

--1.2
showPerson :: Person -> String 
showPerson (Person name age) = "(" ++ showPersonN (Person name age) ++ ", " ++ showPersonA (Person name age) ++ ")"


--1.3
mShowPersonN :: Reader Person String 
mShowPersonN = Reader $ showPersonN >>= \pers -> return pers

mShowPersonA :: Reader Person String 
mShowPersonA = Reader $ showPersonA >>= \pers -> return pers

mShowPerson :: Reader Person String 
mShowPerson = Reader $ showPerson >>= \pers -> return pers 







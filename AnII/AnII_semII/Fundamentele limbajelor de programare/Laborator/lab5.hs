import Data.Char
import Control.Monad
import Control.Applicative

newtype Parser a = Parser {apply :: String -> [(a, String)]}
{-
apply :: Parser a -> String -> [(a, String)]
apply (Parser f) s = f s 


parse :: Parser a -> String -> a 
parse m s = head [x | (x, t) <- apply m s, t == ""]

anychar = Parser f 
    where
        f [] = []
        f (c:s) = [(c, s)]

satisfy :: (Char -> Bool) -> Parser Char 
satisfy p = Parser f
    where 
        f [] = []
        f (c:s) | p c = [(c, s)]
                | otherwise = []
char :: Char -> Parser Char 
char c = satisfy (== c)

string :: String -> Parser String 
string [] = Parser (\s -> [([], s)])
string (x: xs) = Parser f 
    where
        f s = [(y:z, zs)| (y, ys) <- apply (char x) s,
                          (z, zs) <- apply (string xs) ys]
-}

instance Monad Parser where
    return x = Parser (\s -> [(x, s)])
    m >>= k = Parser (\s -> [(y, u) | (x, t) <- apply m s,
                                      (y, u) <- apply (k x) t])

instance Applicative Parser where
    pure = return
    mf <*> ma = do
        f <- mf
        f <$> ma

instance Functor Parser where
    fmap f ma = f <$> ma

anychar :: Parser Char
anychar = Parser f
    where
        f [] = []
        f (c:s) = [(c, s)]

satisfy :: (Char -> Bool) -> Parser Char
satisfy p = Parser f
    where
        f [] = []
        f (c:s) | p c = [(c, s)]
                | otherwise = []
char :: Char -> Parser Char
char c = satisfy (== c)

string :: String -> Parser String
string [] = return []
string (x : xs) = do y <- char x
                     ys <- string xs
                     return (y:ys)


--analiza sintactica
--1 Parserul three
three :: Parser (Char, Char)
three = Parser f
    where
        f (x:xx:xxx:xxxx:xs) = [((x, xxx), xs)]
        f _ = []

--2 Monada Parser 
threeM :: Parser (Char, Char)
threeM = do
            x1 <- anychar
            x2 <- anychar
            x3 <- anychar
            return (x1, x3)

stringM :: String -> Parser String
stringM [] = return []
stringM (x : xs) = do
                        y <- char x
                        ys <- stringM xs
                        return (y:ys)

--3 Functor Parser
anycharord :: Parser Int
anycharord = Parser f
    where
        f [] = []
        f (x : xs) = [(ord x, xs)]

--4 Combinarea alternativelor (MonadPlus)
failM :: Parser a
failM = Parser (\s -> [])

instance MonadPlus Parser where
    mzero = failM
    mplus m n = Parser (\s -> apply m s ++ apply n s)

instance Alternative Parser where 
    empty = mzero 
    (<|>) = mplus

satisfyM :: (Char -> Bool) -> Parser Char 
satisfyM p = do 
                c <- anychar
                if p c then return c else failM

digit :: Parser Char
digit = satisfyM isDigit

abcP :: Parser Char
abcP = satisfyM (`elem` ['A', 'B', 'C'])

alt :: Parser a -> Parser a -> Parser a 
alt p1 p2 = Parser f
    where 
        f s = apply p1 s ++ apply p2 s 

manyP :: Parser a -> Parser [ a ]
manyP p = someP p <|> return [ ]

someP :: Parser a -> Parser [a]
someP p = do 
            x <- p 
            xs <- manyP p
            return (x : xs)

isA :: Parser Char
isA = satisfyM (== 'a')

isB :: Parser Char
isB = satisfyM (== 'b')

isAOrB :: Parser Char
isAOrB = isA <|> isB

--5 do not work
howmany :: Char -> Parser Int
howmany c = fmap (\x -> length(x)) (someP (satisfyM (==c)))

--6 
twocharord :: Parser Int 
twocharord = Parser f 
    where
        f (x:xx:xs) = [(ord x + ord xx, xs)]
        f _ = []

--7
no :: Int -> Int -> Int -> Int -> Int 
no x y z v = x*1000+y*100+z*10 + v

fourdigit :: Parser Int 
fourdigit = Parser f 
    where 
        f (x:y:z:v:xs) = [(no (digitToInt x) (digitToInt y) (digitToInt z) (digitToInt v), xs)] 
        f _ = []
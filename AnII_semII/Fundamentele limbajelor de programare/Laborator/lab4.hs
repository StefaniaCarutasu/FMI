--Interpretarea monadica a programelor
{-
--- Monada Identity
newtype Identity a = Identity { runIdentity :: a }

instance Show a => Show (Identity a) where
  show (Identity a) = show a

instance Monad Identity where
  return a = Identity a
  ma >>= k = k (runIdentity ma)

instance Applicative Identity where
  pure = return
  mf <*> ma = do
                f <- mf
                a <- ma
                return (f a)

instance Functor Identity where
  fmap f ma = pure f <*> ma

--- Limbajul si Interpretorul
type M = Identity

showM :: Show a => M a -> String
showM a = show (runIdentity a)

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


data Value = Num Integer
           | Fun (Value -> M Value)
           | Wrong

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"
 show Wrong   = "<wrong>"

type Environment = [(Name, Value)]

lookupM :: Name -> Environment -> M Value
lookupM val env = case lookup val env of
    Just var -> return var
    Nothing -> return Wrong

add :: Value -> Value -> M Value
add (Num v1) (Num v2) = return (Num $ v1 + v2)
add _ _ = return Wrong

apply :: Value -> Value -> M Value
apply (Fun func) var = func var 
apply _ _ = return Wrong 


interp :: Term -> Environment -> M Value
interp (Var x) env = lookupM x env
interp (Con i) _ = return (Num i)
interp (t1 :+: t2) env = do
                            val1 <- interp t1 env 
                            val2 <- interp t2 env
                            add val1 val2
interp (Lam x t) env = return $ Fun $ \v -> interp t ((x, v): env)
interp (App t1 t2) env = do 
                            func <- interp t1 env
                            var <- interp t2 env 
                            apply func var

term0 :: Term
term0 = (App (Lam "x" (Var "x" :+: Var "x")) (Con 10 :+: Con 11))


--MAYBE
type M a = Maybe a

showM :: Show a => M a -> String
showM (Just a) = show a
showM Nothing = "<Wrong>" 

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


data Value = Num Integer
           | Fun (Value -> M Value)

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"

type Environment = [(Name, Value)]

lookupM :: Name -> Environment -> M Value
lookupM var env = lookup var env

add :: Value -> Value -> M Value
add (Num v1) (Num v2) = return (Num $ v1 + v2)
add _ _ = Nothing 

apply :: Value -> Value -> M Value
apply (Fun func) var = func var 
apply _ _ = Nothing  


interp :: Term -> Environment -> M Value
interp (Var x) env = lookupM x env
interp (Con i) _ = return (Num i)
interp (t1 :+: t2) env = do
                            val1 <- interp t1 env 
                            val2 <- interp t2 env
                            add val1 val2
interp (Lam x t) env = return $ Fun $ \v -> interp t ((x, v): env)
interp (App t1 t2) env = do 
                            func <- interp t1 env
                            var <- interp t2 env 
                            apply func var
                            
--EITHER

type M a = Either String a 

showM :: Show a => M a -> String
showM (Right a) = show a
showM (Left err) = "Error: " ++ err  

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


data Value = Num Integer
           | Fun (Value -> M Value)

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"

type Environment = [(Name, Value)]

lookupM :: Name -> Environment -> M Value
lookupM var env = case lookup var env of 
    Just val -> return val 
    Nothing -> Left ("unbound variable: "++ var)

add :: Value -> Value -> M Value
add (Num v1) (Num v2) = return (Num $ v1 + v2)
add v1 v2 = Left ("should be numbers: " ++ show v1 ++ ", " ++ show v2) 

apply :: Value -> Value -> M Value
apply (Fun func) var = func var 
apply f _ = Left ("Shoul be function: " ++ show f)



interp :: Term -> Environment -> M Value
interp (Var x) env = lookupM x env
interp (Con i) _ = return (Num i)
interp (t1 :+: t2) env = do
                            val1 <- interp t1 env 
                            val2 <- interp t2 env
                            add val1 val2
interp (Lam x t) env = return $ Fun $ \v -> interp t ((x, v): env)
interp (App t1 t2) env = do 
                            func <- interp t1 env
                            var <- interp t2 env 
                            apply func var


--CU LISTE
type M a = [a]

showM :: Show a => M a -> String
showM = show  

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
          | Amb Term Term
          | Fail
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


data Value = Num Integer
           | Fun (Value -> M Value)

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"

type Environment = [(Name, Value)]

lookupM :: Name -> Environment -> M Value
lookupM var env = case lookup var env of 
    Just val -> return val 
    Nothing -> []

add :: Value -> Value -> M Value
add (Num v1) (Num v2) = return (Num $ v1 + v2)
add _ _ = []

apply :: Value -> Value -> M Value
apply (Fun func) var = func var 
apply _ _ = []


interp :: Term -> Environment -> M Value
interp Fail _ = []
interp (Var x) env = lookupM x env
interp (Con i) _ = return (Num i)
interp (t1 :+: t2) env = do
                            val1 <- interp t1 env 
                            val2 <- interp t2 env
                            add val1 val2
interp (Lam x t) env = return $ Fun $ \v -> interp t ((x, v): env)
interp (App t1 t2) env = do 
                            func <- interp t1 env
                            var <- interp t2 env 
                            apply func var
interp (Amb t1 t2) env = interp t1 env ++ interp t2 env



--READER (GOD HELP ME)
--- Monada Reader
type Environment = [(Name, Value)]

newtype EnvReader a = EnvReader {runEnvReader :: Environment -> a}

instance Show a => Show (EnvReader a) where
  show ma = show $ runEnvReader ma []

instance Monad EnvReader where
  return x = EnvReader (\_ -> x)
  ma >>= k = EnvReader f
    where f env = let a = runEnvReader ma env
                  in runEnvReader (k a) env 

instance Applicative EnvReader where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)

instance Functor EnvReader where
  fmap f ma = pure f <*> ma

-- intoarcere starea curenta
ask :: EnvReader Environment
ask = EnvReader id

-- modificare stare doar pt computatia data
local :: (Environment -> Environment) -> EnvReader a -> EnvReader a
local f ma = EnvReader $ (\env -> (runEnvReader ma )(f env))

--- Limbajul si Interpretorul
type M a = EnvReader a

showM :: Show a => M a -> String
showM = show

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


data Value = Num Integer
           | Fun (Value -> M Value)
           | Wrong

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"
 show (Wrong) = "<wrong>"

lookupM :: Name -> M Value
lookupM var = do
                env <- ask
                case lookup var env of
                  Just val -> return val
                  Nothing -> return Wrong

add :: Value -> Value -> M Value
add (Num nr1) (Num nr2) = return (Num $ nr1 + nr2)
add _ _ = return Wrong

apply :: Value -> Value -> M Value
apply (Fun func) var = func var
apply _ _ = return Wrong

interp :: Term -> M Value
interp (Var x) = lookupM x
interp (Con nr) = return (Num nr)
interp (t1 :+: t2) = do
                        var1 <- interp t1
                        var2 <- interp t2
                        add var1 var2
interp (Lam x t) = do
                        env <- ask
                        return $ Fun $ \v -> local (const ((x, v):env)) (interp t)
interp (App t1 t2) = do
                        func <- interp t1
                        var <- interp t2
                        apply func var

test :: Term -> String
test t = showM $ interp t

pgm1 :: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          ((Con 10) :+:  (Con 11))

pgm2 :: Term
pgm2 = (App (Con 7) (Con 2))
          
-- test pgm
-- test pgm1

--WRITER

newtype StringWriter a = StringWriter { runStringWriter :: (a, String) }

instance Show a => Show (StringWriter a) where 
    show ma = "Output: " ++ sir ++ " Value: " ++ show a 
        where (a, sir) = runStringWriter ma

instance Monad StringWriter where
    return x = StringWriter (x, "")
    ma >>= k = let
                    (a, s1) = runStringWriter ma 
                    (b, s2) = runStringWriter (k a)
                in 
                    StringWriter(b, s1 ++ s2)

instance Applicative StringWriter where
    pure = return 
    mf <*> ma = do
        f <- mf 
        a <- ma 
        return (f a)

instance Functor StringWriter where
    fmap f ma = pure f <*> ma 

--producere mesaj 
tell :: String -> StringWriter ()
tell sir = StringWriter((), sir)


--Limbajul si interpretorul
type M a = StringWriter a

showM :: Show a => M a -> String 
showM = show 

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
          | Out Term
  deriving (Show)

data Value = Num Integer
           | Fun (Value -> M Value)
           | Wrong

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"
 show (Wrong) = "<wrong>"

type Environment = [(Name, Value)]

lookupM :: Name -> Environment -> M Value
lookupM var env = case lookup var env of
  Just val -> return val
  Nothing -> return Wrong

add :: Value -> Value -> M Value
add (Num nr1) (Num nr2) = return (Num $ nr1 + nr2)
add _ _ = return Wrong

apply :: Value -> Value -> M Value
apply (Fun func) var = func var
apply _ _ = return Wrong

interp :: Term -> Environment -> M Value
interp (Var x) env = lookupM x env
interp (Con nr) _ = return (Num nr)
interp (t1 :+: t2) env = do
                            var1 <- interp t1 env
                            var2 <- interp t2 env
                            add var1 var2
interp (Lam x t) env = return $ Fun $ \v -> interp t ((x, v):env)
interp (App t1 t2) env = do
                        func <- interp t1 env
                        var <- interp t2 env
                        apply func var
interp (Out t) env = do 
                        val <- interp t env 
                        tell(show val ++ "; ")
                        return val
-}


--STATE

newtype IntState a = IntState {runIntState :: Integer -> (a, Integer )}

instance Show a => Show (IntState a) where
    show ma = "Value: " ++ show a ++ " Count: " ++ show state
        where (a, state) = runIntState ma 0

instance Monad IntState where
    return x = IntState (\s -> (x, s))
    ma >>= k = IntState (\state -> let (a, state1) = runIntState ma state
                                   in runIntState (k a) state1)


instance Applicative IntState where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)

instance Functor IntState where
    fmap f ma = pure f <*> ma

--schimbare de stare
modify :: (Integer -> Integer) -> IntState ()
modify fun = IntState (\s -> ((), fun s))

--creste stare contor
tickS :: IntState ()
tickS = modify (+1)

--obtinere stare curenta
get :: IntState Integer
get = IntState (\s -> (s, s))

--Limbajul si interpretorul
type M a = IntState a

showM :: Show a => M a -> String
showM = show

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
          | Count
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


data Value = Num Integer
           | Fun (Value -> M Value)
           | Wrong

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"
 show Wrong = "<wrong>"

type Environment = [(Name, Value)]

lookupM :: Name -> Environment -> M Value
lookupM var env = case lookup var env of
  Just val -> return val
  Nothing -> return Wrong

add :: Value -> Value -> M Value
add (Num nr1) (Num nr2) = tickS >> return (Num $ nr1 + nr2)
add _ _ = return Wrong

apply :: Value -> Value -> M Value
apply (Fun func) var = tickS >> func var
apply _ _ = return Wrong

interp :: Term -> Environment -> M Value
interp (Var x) env = lookupM x env
interp (Con nr) _ = return (Num nr)
interp (t1 :+: t2) env = do
                            var1 <- interp t1 env
                            var2 <- interp t2 env
                            add var1 var2
interp (Lam x t) env = return $ Fun $ \v -> interp t ((x, v):env)
interp (App t1 t2) env = do
                        func <- interp t1 env
                        var <- interp t2 env
                        apply func var
interp Count _ = do
                    count <- get
                    return (Num count)
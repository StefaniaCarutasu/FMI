myInt = 5555555555555555555555555555555555555555555555555555555555555555555555555555555555555
myInt1 = 5555555555555555555555555555555555555555555555555555555555555555555555555555555555555
double :: Integer -> Integer
double x = x+x


--maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
            else y
maxim2 (x , y) = if (x > y)
               then x
            else y
max3 x y z = let
             u = maxim x y
             in (maxim  u z)

--triple :: Integer -> Integer
triple x = 3*x

maxim3 x y z = maxim x (maxim y z)

max3' (x, y, z) = 
    let
        u = maxim x y
    in
        maxim u z

max4 x y z w = let
    u = maxim x y
    a = maxim z w
    in maxim2 (u, a)

maxim4 x y z w = maxim (maxim x y) (maxim z w)
max4' x y z w = maxim x (maxim3 y z w)

data Alegere
    = Piatra
    | Foarfeca
    | Hartie
    deriving (Eq, Show)


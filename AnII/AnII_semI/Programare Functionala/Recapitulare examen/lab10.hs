import Data.String
import Prelude hiding (lookup)
import qualified Data.List as List
import Test.QuickCheck
import Test.QuickCheck.Gen

semigroupAssoc :: (Eq m, Semigroup  m) => m -> m -> m -> Bool 
semigroupAssoc a b c = (a <> (b <> c)) == ((a <> b) <> c)

monoidLeftIdentity :: (Eq m, Monoid m) => m -> Bool 
monoidLeftIdentity a = (mempty <> a) == a

monoidRightIdentity :: (Eq m, Monoid m) => m -> Bool 
monoidRightIdentity a = (a <> mempty ) == a

--1
data Trivial = Trivial
    deriving (Eq, Show)

instance Semigroup Trivial where
    _ <> _ = Trivial

instance Monoid Trivial where
    mempty = Trivial

instance Arbitrary Trivial where
    arbitrary = elements [Trivial]

type TrivAssoc = Trivial -> Trivial -> Trivial -> Bool 
type TrivId = Trivial -> Bool 

-- >    quickCheck (semigroupAssoc :: TrivAssoc)
-- >    quickCheck (monoidLeftIdentity :: TrivId)
-- >    quickCheck (monoidRightIdentity :: TrivId)

--2 (Conjunctii)

newtype BoolConj = BoolConj Bool
    deriving (Eq, Show)

instance Semigroup BoolConj where
    BoolConj a <> BoolConj b = BoolConj (a && b)

instance Monoid BoolConj where
    mempty = BoolConj True  

instance Arbitrary BoolConj where
    arbitrary  = MkGen (\s i -> BoolConj ((unGen arbitrary ) s i))

type BoolConjAssoc = BoolConj -> BoolConj -> BoolConj -> Bool
type BoolConjId = BoolConj -> Bool

--3 (Disjunctii)

newtype BoolDisj = BoolDisj Bool
    deriving (Eq, Show)

instance Semigroup BoolDisj where
    BoolDisj a <> BoolDisj b = BoolDisj (a || b)

instance Monoid BoolDisj where 
    mempty = BoolDisj False 

type BoolDisjAssoc = BoolDisj -> BoolDisj -> BoolDisj -> Bool
type BoolDisjId = BoolDisj -> Bool

--4 (Identity)

newtype Identity a = Identity a
    deriving (Eq, Show)

instance Semigroup a => Semigroup (Identity a) where
    Identity a <> Identity b = Identity (a <> b)

instance Monoid a => Monoid  (Identity a) where
    mempty = Identity mempty 

type IdentityAssoc a = Identity a -> Identity a -> Identity a -> Bool
type IdentityId a = Identity a -> Bool

--5 (Pereche)

data Two a b = Two a b
    deriving (Eq, Show)

instance (Semigroup a, Semigroup b) => Semigroup (Two a b) where
    Two x y <> Two z t = Two (x <> z) (y <> y)

instance (Monoid a, Monoid b) => Monoid (Two a b) where
    mempty = Two mempty mempty 

type TwoAssoc a b = Two a b -> Two a b -> Two a b -> Bool
type TwoId a b = Two a b -> Bool

--6 (Alternativa)

data Or a b = Fst a | Snd b
    deriving (Eq, Show)

instance  Semigroup (Or a b) where 
  Fst _ <> x =  x
  y     <> _ =  y

type OrAssoc a b = Or a b -> Or a b -> Or a b -> Bool
type OrId a b = Or a b -> Bool
f :: a -> m 
foldMap f tr = foldr foo i tr
                where 
                    i = mempty 
                    foo :: (a -> m -> m)
                    foo = \x acc -> f x <> acc
                        = \x acc -> (<>) (f x) acc 
                        = \x -> ((<>) . f) x
                        = (<>) . f
--foldMap cu foldr
foldMap f = foldr ((<>).f) mempty 

--Foldable cu foldMap
instance Foldable BinaryTree where
    foldMap f (Leaf x) = f x
    foldMap (Node l r) = foldMap f l <> foldMap f r
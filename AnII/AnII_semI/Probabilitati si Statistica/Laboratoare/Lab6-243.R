#Lucru cu discreteRV
#Crearea unei v.a.
library(discreteRV)
X <- RV(1:100)
#P(X<5)
P(X<5)
#Folosim functia fractions din pachetul MASS
fractions(P(X<5))
#P(X=5)
P(X==5)
#P(8<X<23)
fractions(P((X>8)%AND%(X<23)))
#P(X>2 sau X<8)
P((X>2)%OR%(X<8))
#Calcul de probabilitati conditionate
#P(X<27|X>=3)=P(3<=X<27)/P(X>=3)=24/98
a <- P(X<27|X>=3)
str(a)
b <- P(X==5)
fractions(0.244898)
fractions(as.numeric(a))
fractions(a[1])
#ATENTIE: fractions vrea mereu un numar, nu un altfel de obiect
#totusi, stie sa lucreze cu vectori
fractions(c(0.5,0.8))
X1 <- RV(1:3, c(1/3,1/6,1/2))
plot(X1)
plot(X)

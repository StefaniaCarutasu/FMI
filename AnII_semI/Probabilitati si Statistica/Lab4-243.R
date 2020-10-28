#Lucru cu pachetul prob
#Aruncarea cu moneda

t3 <- tosscoin(3)
str(t3)
t3$toss2
##################################
###Extragerea de subvectori dintr-un vector
a <- 1:100
a1 <- a[1:43]
a1 <- c(a[1:43],a[89])
a2 <- a[c(1:43,89)]
a3 <- a[-2]
a4 <- a[a%%2==0]
a5 <- a[(a%%3==0)&!(a%%5==0)]
####################################
t3[1,]
t3[,1]
#Se arunca o moneda de 3 ori si vrem probabilitatea de aparitie cel putin
#de 2 ori a H

#Se arunca o moneda o data si vrem probabilitatea de aparitie a H
omega1 <- tosscoin(1)
sum(omega1=='H')/nrow(omega1)

#Revenim la problema cu 3 aruncari
omega3 <- tosscoin(3)
sum(rowSums(omega3=='H')>=2)/nrow(omega3)

#Calculati probabilitatea de aparitie a secventei TT la aruncarea monedei de 3 ori

#Claudia Dudau
probTT31 <- (sum((omega3[,1] == 'T') & (omega3[,2] == 'T')) + sum((omega3[,2] == 'T') & (omega3[,3] == 'T')))/ nrow(omega3)

#Calculati probabilitatea de aparitie a secventei TT la aruncarea monedei de 5 ori


#Aruncarea unui zar
zar2 <- rolldie(2)
str(zar2)
# Determinati probabilitatea ca la aruncarea a doua zaruri sa se obtina
#suma 7
#Cosmin Petrescu
sum(zar2[,1]+zar2[,2]==7)

#Radu-Andrei Onea /Claudia Dudau
h <- sum(rowSums(zar2)==7)/nrow(zar2)

#Alta varianta
t <- table(rowSums(zar2))/nrow(zar2)
str(t)
#Radu
t[['7']]

#Jocuri de carti
s <- cards()
str(s)
# Determinati probabilitatea de a extrage o carte de Inima
#Radu
sum(s['suit']=='Heart')/nrow(s)

#Radu
(table(s["suit"])/nrow(s))[["Heart"]]

#To DO: operatii cu evenimente(union, intersect, setdiff)
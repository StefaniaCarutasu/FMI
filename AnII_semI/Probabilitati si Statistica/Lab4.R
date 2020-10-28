
t3 <- tosscoin(3)
str(t3)
t3$toss2
a <- 1:100
a1 <- a[1:43]
a1 <- c(a[1:43], a[89])
a2 <- a[c(1:43, 89)]
a3 <- a[-2]
a4 <- a[a%%2==0]
a5 <- a[(a%%3 == 0) &!(a%%5 == 0)]

t3[1,]
t3[,1]

#Se arunca o moneda o singura data si vrem 
#probabilitatea sa apara H

omega1 <- tosscoin(1)
sum(omega1 == 'H')/nrow(omega1)

#Revenim la problema cu 3 aruncari
omega3 <- tosscoin(3)
sum(rowSums (omega3 == 'H') >= 2) / nrow(omega3)

#Probabilitatea aparitiei secventei TT la aruncarea
#monedei de 3 ori
probTT31 <- (sum((omega3[,1] == 'T') & (omega3[,2] == 'T')) + sum((omega3[,2] == 'T') & (omega3[,3] == 'T')))/ nrow(omega3)


#Aruncarea cu zarul
zar2 <- rolldie(2)
zar2$X1

#Det prob ca la aruncarea a doua zaruri sa se 
#obtina 7

sum(zar2[,1]+zar2[,2] == 7)

h <- sum(rowSums(zar2) == 7)/nrow(zar2)

t <- table(rowSums(zar2))/nrow(zar2)
str(t)

#Jocuri de carti

s <- cards()
str(s)

#Det probabilitatea de a extrage o carte de inima
length(s[s['suit'] == 'Heart'])

sum(s['suit'] == 'Heart')/nrow(s)

(table(s['suit'])/nrow(s))[["Heart"]]


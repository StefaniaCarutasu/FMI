"""
#Problema cu copaci
def citireDate():
    f = open("dreptunghi.txt")

    aux = f.readline().split()
    xst = int(aux[0])
    yst = int(aux[1])
    aux = f.readline().split()
    xdr = int(aux[0])
    ydr = int(aux[1])

    coordonateCopaci = []
    for linie in f:
        aux = linie.split()
        coordonateCopaci += [(int(aux[0]), int(aux[1]))]

    f.close()

    return xdr, ydr, xst, yst, coordonateCopaci
def dreptunghiArieMaxima(xst, yst, xdr, ydr):
    global arieMaxima, coordonateGauri, dMaxim

    for g in coordonateCopaci:
        if xst < g[0] < xdr and yst < g[1] < ydr:
            dreptunghiArieMaxima(xst, yst, g[0], ydr)
            dreptunghiArieMaxima(g[0], yst, xdr, ydr)
            dreptunghiArieMaxima(xst, yst, xdr, g[1])
            dreptunghiArieMaxima(xst, g[1], xdr, ydr)
            break
    else:
        if (xdr-xst)*(ydr-yst) > arieMaxima:
            arieMaxima = (xdr-xst)*(ydr-yst)
            dMaxim = (xst, yst, xdr, ydr)

xdr, ydr, xst, yst, coordonateCopaci = citireDate()
arieMaxima = 0
dMaxim = (0, 0, 0, 0)
dreptunghiArieMaxima(xst, yst, xdr, ydr)
print(arieMaxima)
print(dMaxim)
"""
#Problema cu aparitii
def caut_bin(x, st, dr):
   m = (st + dr) // 2
   if st > dr:
       print(0)
       return 0
   if x == l[m]:
       nr = 1
       i = m+1
       while i < len(l) and l[i] == x:
           nr += 1
           i += 1
       i = m-1
       while i>=0 and l[i] == x:
           nr += 1
           i -= 1
       print(nr)
       return 0
   elif x > l[m]:
       caut_bin(x, m+1, dr)
   else:
       caut_bin(x, st, m-1)

f = open('input.txt')
l = [int(x) for x in f.readline().split()]
print(l)
l.sort()
n = int(input())
caut_bin(n, 0, len(l))


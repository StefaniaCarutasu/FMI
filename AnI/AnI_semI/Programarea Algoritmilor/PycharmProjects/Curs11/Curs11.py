'''
#generarea permutarilor
global n, s
def bkt(k):
    if k==n: print(s)
    for i in range(1,n+1):
        if i not in S:
            sol[k]=i
            if k<n:
                bkt(k+1)
            k-=1


n=5
s=[0]*n
bkt(0)
'''
#problema damelor
global n
def printsol(tabla):
    fir i in range(n):
    printt(tabla[i])
def check(tabla, row, col):
    for i in range(row):
        if tabla[row][i]==1:
            return False
    for i in range(col)
        if tabla[i][col]==1
             return False
    i=row-1; j=col+1
    while i>=0 and j>=0:
        if tabla[i][j]==1
            return False
        i-=1; j-=1
    while i>=0 and j<n:
        if tabla[i][j]==1
            return False
        i-=1; j+=1
    return True
def bkt(tabla, col):
    if col==n: return True
    for i in range(n):
        if check(tabla,i,col):
            tabla[i][col]=1
            if bkt(tabla,col+1):
                return True
            tabla[i][col]=0
    return False



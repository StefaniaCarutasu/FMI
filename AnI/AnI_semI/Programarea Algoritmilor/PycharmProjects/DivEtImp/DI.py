"""
#Merge sort
a=[1,89,67,12,56,6,74,8,0,3]
def sort(p, q, a):
    if a[p]>a[q]:
        m=a[p]; a[p]=a[q]; a[q]=m
def interclasare(p, q, m, a):
    b=[]
    i=p; j=m
    while i<m and j<q:
        if a[i]<=a[j]:
            b.append(a[i])
            i+=1
        else:
            b.append(a[j])
            j+=1
    while i<m:
        b.append(a[i])
        i+=1
    while j<q:
        b.append(a[j])
        j+=1
    a[p:q]=b[0:len(b)]
def DivImp(p, q, a):
    if q-p<=1:
        sort(p,q,a)
    else:
        m=(p+q)//2
        DivImp(p, m, a)
        DivImp(m+1, q, a)
        interclasare(p, q, m, a)

n=len(a)-1
DivImp(0, n-1, a)
print(a)

#Mediana a 2 vectori sortati de dim diferite
def mediana(v1, v2,n,m):
    if n<=2:
        w=[]
        if m%2==0:
            w.append(v2[m//2]);  w.append(v2[m//2-1])
        else: w.append(v2[m//2])
        v=[]
        i=0; j=0
        while i<n and j<len(w):
            if v1[i]<=w[j]:
                v.append(v1[i]); i+=1
            else: v.append(w[j]); j+=1
        while i<n:
            v.append(v1[i])
        while j<len(w):
            v.append(w[j])
        if len(v)%2==0:
            return (v[len(v)//2]+v[len(v)//2-1])/2
        else:
            return v[len(v)//2]
    else:
        if n%2==2:
            x=(v1[n//2]+v1[n//2-1])/2
        else: x=v1[n//2]
        if m%2==2:
            y=(v2[m//2]+v2[m//2-1])/2
        else: y=v2[m//2]
        if x==y:
            return x
        elif x<y:
            v1=v1[n//2:]
            n//=2
            v2=v2[:m-n//2]
            m-=n//2
        elif x>y:
            v1=v1[:n//2+1]; n//=2
            v2=v2[n//2:]; m-=n//2
        return mediana(v1, v2, n, m)


#f = open('input.txt')
n = 6
v = [1, 2, 3, 4, 5, 6]
m = 7
w = [1, 2, 3, 4, 5, 6, 7]
print(mediana(v, w, n, m))
"""
"""
#Problema panzei cu n gauri
def arieMax(left,up, right, down):
    global maxs, listateGauri
    ok=True
    for g in listaGauri:
        if up<g[0]<down and left<g[1]<right:
            ok=False
            arieMax(left, up, g[1], down)
            arieMax(g[1], up, right, down)
            arieMax(left, g[0], right, down)
            arieMax(left, up, right, g[0])
    if ok:
        sup=(right-left)*(down-up)
        if maxs<sup:
            maxs=sup
            #coord=(up,left,down, right)
    return maxs
f=open("input.txt","r")
n=int(f.readline())
m=int(f.readline())
listaGauri=[]
for line in f:
    x=line.split()
    x[0]=int(x[0]); x[1]=int(x[1])
    x=tuple(x)
    listaGauri.append(x)
f.close()
maxs=0
print(listaGauri)
print(arieMax(0,0,n,m))


# Cel de-al k-lea minim dintr-un vector
# a) varianta cu min heap
import heapq
H=[10, 3, 15, 20, 7, 19, 30, 32, 1, 5, 15,1, 3]
k=int(input())
heapq.heapify(H)
ult=H[0]
heapq.heappop(H)
k-=1
while k>1:
    if ult==H[0]:
        heapq.heappop(H)
        ult=H[1]
    else:
        k-=1
        heapq.heappop(H)
        ult=H[1]
print(H[0])
"""
"""
# b) varianta cu quick select
def quick_select(v, k):
    piv=v[0]
    st=[]; dr=[]
    for e in v[1:]:
        if e<piv: st.append(e)
        else: dr.append(e)
    m=len(st)
    if m==k-1: return piv
    if m>k-1: return quick_select(st,k)
    return quick_select(dr, m+1)
l=[10,3,20,7,19,30,32,1,5,15]
k=3
print(quick_select(l,k))
"""
"""
n = int(input())
x = int(input())
y = int(input())
row = [0] * (2 ** n + 1)
b = []
no = 0
for i in range(0, 2 ** n + 1):
    row = [0] * (2 ** n + 1)
    b.append(row)
b[x][y] = -1
cad = 0


def bordare(xb, yb, xh, yh, n):
    h = n // 2
    xc = 0
    yc = 0
    global no
    xc = xb + h - 1;
    yc = yb + h - 1
    if n == 2:
        if b[xb][yb + 1] == 0 and b[xb + 1][yb] == 0 and b[xb + 1][yb + 1] == 0:
            no += 1;
            b[xb][yb + 1] = no;
            b[xb + 1][yb] = no;
            b[xb + 1][yb + 1] = no
        if b[xb][yb] == 0 and b[xb + 1][yb] == 0 and b[xb + 1][yb + 1] == 0:
            no += 1;
            b[xb][yb] = no;
            b[xb + 1][yb] = no;
            b[xb + 1][yb + 1] = no
        if b[xb][yb + 1] == 0 and b[xb][yb] == 0 and b[xb + 1][yb + 1] == 0:
            no += 1;
            b[xb][yb + 1] = no;
            b[xb][yb] = no;
            b[xb + 1][yb + 1] = no
        if b[xb][yb + 1] == 0 and b[xb + 1][yb] == 0 and b[xb][yb] == 0:
            no += 1;
            b[xb][yb + 1] = no;
            b[xb + 1][yb] = no;
            b[xb][yb] = no
        return
    if xh <= xc:
        if yh <= yc:
            if b[xc][yc + 1] == 0 and b[xc + 1][yc] == 0 and b[xc + 1][yc + 1] == 0:
                no += 1;
                b[xc][yc + 1] = no;
                b[xc + 1][yc] = no;
                b[xc + 1][yc + 1] = no;
                cad = 1
        else:
            if b[xc][yc] == 0 and b[xc + 1][yc] == 0 and b[xc + 1][yc + 1] == 0:
                no += 1;
                b[xc][yc] = no;
                b[xc + 1][yc] = no;
                b[xc + 1][yc + 1] = no;
                cad = 2
    else:
        if yh <= yc:
            if b[xc][yc + 1] == 0 and b[xc][yc] == 0 and b[xc + 1][yc + 1] == 0:
                no += 1;
                b[xc][yc + 1] = no;
                b[xc][yc] = no;
                b[xc + 1][yc + 1] = no;
                cad = 3
        else:
            if b[xc][yc + 1] == 0 and b[xc + 1][yc] == 0 and b[xc][yc] == 0:
                no += 1;
                b[xc][yc + 1] = no;
                b[xc + 1][yc] = no;
                b[xc][yc] = no;
                cad = 4
    if cad == 1:
        bordare(xb, yb, xh, yh, h)
        bordare(xb, yc + 1, xc, yc + 1, h)
        bordare(xc + 1, yb, xc + 1, yc, h)
        bordare(xc + 1, yc + 1, xc + 1, yc + 1, h)
    if cad == 2:
        bordare(xb, yb, xc, yc, h)
        bordare(xb, yc + 1, xh, yh, h)
        bordare(xc + 1, yb, xc + 1, yc, h)
        bordare(xc + 1, yc + 1, xc + 1, yc + 1, h)
    if cad == 3:
        bordare(xb, yb, xc, yc, h)
        bordare(xb, yc + 1, xc, yc + 1, h)
        bordare(xc + 1, yb, xh, yh, h)
        bordare(xc + 1, yc + 1, xc + 1, yc + 1, h)
    if cad == 4:
        bordare(xb, yb, xc, yc, h)
        bordare(xb, yc + 1, xc, yc + 1, h)
        bordare(xc + 1, yb, xc + 1, yc, h)
        bordare(xc + 1, yc + 1, xh, yh, h)


bordare(1, 1, x, y, 2 ** n)

for i in range(1, 2 ** n + 1):
    for j in range(1, 2 ** n + 1):
        if b[i][j] == -1:
            print("X", end=" ")
        else:
            print(b[i][j], end=" ")
print()
"""

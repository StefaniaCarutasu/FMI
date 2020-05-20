f=open("date.in","r")
n=int(f.readline())
a=f.readline()
a=a.split()
for i in range(len(a)):
   a[i]=int(a[i])

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

DivImp(0, n-1, a)
print(a)
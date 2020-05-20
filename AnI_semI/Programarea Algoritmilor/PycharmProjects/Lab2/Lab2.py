"""
#Problema 1
prop=input()
greseala=input()
corect=input()
prop=prop.replace(greseala,corect,len(prop))
print(prop)

#Problema 2
prop=input()
for i in range(len(prop)):
    if i==0:
        prop[i]=prop[i].upper()
    elif prop[i-1]==' ' and prop[i]!=' ':
        prop[i] = prop[i].upper()
print(prop)

#Problema 3
prop=input()
s=input()
t=input()
prop2=str()
prop=prop.split(' ')
for x in prop:
    if x!=s:
        prop2+=x+' '
    else:
       prop2+=t+' '

print(prop2)

#Problema 4
cuv1=input()
cuv2=input()
for i in range(len(cuv1)):
    for j in range(len(cuv2)):
        if cuv2[j]==cuv1[i]:
            cuv2=cuv2[:j]+cuv2[j+1:]
if cuv2=='':
    print("Anagrame")
else: print("Tzeapa")
#Problema 5
text="Ana are multe mere frumoase"
k=3
alfabet="abcdefghijklmnopqrstuvwxyz"
for i in range(len(text)):
    if text[i] != ' ':
       j=0
       while alfabet[j] != text[i]:
           j+=1
       k=(j+i)%26
       text[i]=alfabet[k]
print()
"""
#Problema 6
fraza="Astăzi am cumpărat pâine de 5 RON, pe lapte am dat 10 RON, iar de 15 RON am cumpărat niște cașcaval. De asemenea, mi-am cumpărat și niște papuci cu 50 RON!"
sum=0
cifre="0123456789"
fraza=fraza.split()
for x in fraza:
    for i in range(len(cifre)):
        if x[0]==cifre[i]:
            sum+=int(x)
print(sum)
"""
#Problema 7
data_curenta="1 01 2020"
data_curenta=data_curenta.split(' ')
data="01 01 1782"
data=data.split(' ')
zi_sapt="duminica"
zi=1
nr_zile=1
dict={
    1: "duminica",
    2: "luni",
    3: "marti",
    4: "miercuri",
    5: "joi",
    6: "vineri",
    7: "sambata"
}
an={
    "01": 31,
    "02": 28,
    "03": 31,
    "04": 30,
    "05": 31,
    "06": 30,
    "07": 31,
    "08": 31,
    "09": 28,
    "10": 31,
    "11": 30,
    "12": 31,
}
a=data[2]
b=data_curenta[2]
for an in range(1782,2019):
   if an%4==0 and an%100!=0:
       nr_zile+=366
   elif an%1000==0:
       nr_zile+=366
   else: nr_zile+=365
for luna in range(int(data[1]),int(data_curenta[1])-1):
    nr_zile+=int(an[luna])
nr_zile+=int(data_curenta[0])
nr_zile%=7
print(dict[nr_zile])


#Problema 8 a)
text="Apanapa aparepe meperepe."
t=''
vocale="aeiouAEIOU"
l=len(text)
i=0
while i<l:
    if vocale.find(text[i]):
        t+=text[i]
        i+=3
   # elif text[i]=='p' and text[i-1]==text[i+1] and vocale.find(text[i-1]): # un p intre 2 voc identice=pasareasca
        #i+=2
    else:
        t+=text[i]
        i+=1
print(t)
"""
#Problema 8 b)
text="Ana are mere."
t=''
i=0
k=len(text)
vocale="AEIOUaeiou"
while i<len(text):
    if text[i]==' ' or text[i]=='.':
        t+=text[i]
        i+=1
    elif vocale.find(text[i])!=-1:
        t+=text[i]+'p'+text[i].lower()
        i+=1
    else:
        t+=text[i]
        i+=1
print(t)





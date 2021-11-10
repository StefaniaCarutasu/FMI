f = open("date.in")
"""
#minmizare timp asteptare
def citire():
    timpi = f.readline().split()
    persoane_timpi = {i + 1:int(timpi[i]) for i in range(len(timpi))}
    return persoane_timpi

pt = citire()
pt = sorted(pt.items(), key=lambda x: x[1])
s = 0
timpi = []
for i in pt:
    s += i[1]
    timpi.append(s)
s = sum(timpi)
print("Timpul mediu de asteptare este: ", s/len(pt))


#planificare spectacole intr-o singura sala
def citire():
    n = int(f.readline())
    intervale = []
    for i in range(n):
        s = f.readline().split()
        sp = []
        aux = s[0].split(':')
        a = int(aux[0]) + int(aux[1]) / 100
        sp.append(a)
        aux = s[1].split(':')
        a = int(aux[0]) + int(aux[1]) / 100
        sp.append(a)
        intervale.append(sp)
    return intervale

intervale = citire()
print(intervale)

intervale.sort(key=lambda x: x[1])
print(intervale)

programari = []
for i in intervale:
    if len(programari) == 0:
        programari.append(i)
    else:
        if i[0] > programari[len(programari) - 1][1]:
            programari.append(i)
print(programari)

#planificare in numar minim de sali
def citire():
    n = int(f.readline())
    intervale = []
    for i in range(n):
        s = f.readline().split()
        sp = []
        aux = s[0].split(':')
        a = int(aux[0]) + int(aux[1]) / 100
        sp.append(a)
        aux = s[1].split(':')
        a = int(aux[0]) + int(aux[1]) / 100
        sp.append(a)
        intervale.append(sp)
    return intervale

spectacole = citire()
spectacole.sort(key=lambda x: x[0])
sali = {1:[]}
k = 1
for i in spectacole:
    if len(sali[1]) == 0:
        sali[1].append(i)
    else:
        ok = 0
        for j in sali.keys():
            if sali[j][len(sali[j]) - 1][1] < i[0]:
                sali[j].append(i)
                ok = 1
                break
        if ok == 0:
            k += 1
            sali[k] = []
            sali[k].append(i)
print(sali)


#rucsac
def citire():
    G = int(f.readline())
    obiecte = []
    i = f.readline()
    while i:
        v, g = i.split()
        v, g = int(v), int(g)
        obiecte.append([v, g])
        i = f.readline()
    return obiecte, G

obiecte, G = citire()
obiecte.sort(key=lambda x: x[0]/x[1], reverse=True)
print(obiecte)
rucsac = []
valoare = 0
for i in obiecte:
    if G >= i[1]:
        G -= i[1]
        valoare += i[0]
        rucsac.append(i)
    elif G > 0:
        valoare += (i[0] * G)/i[1]
        rucsac.append([G, (i[0] * G)/i[1]])
        G = 0
print(rucsac)
"""
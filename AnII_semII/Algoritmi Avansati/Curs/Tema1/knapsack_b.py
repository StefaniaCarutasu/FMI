f = open("date.in")
K = int(f.readline())
suma = 0
for obiect in f.readline().split():
    obiect = int(obiect)
    suma += obiect
    if suma > K:
        suma -= obiect
        if obiect > suma:
            suma = obiect

print(suma)
f.close()
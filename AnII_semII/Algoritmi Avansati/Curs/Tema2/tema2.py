import math
import numpy as np
import copy
import matplotlib.pyplot as plt
f = open('alg_genetici.in')
g = open('Evolutie.txt', 'w')

def citire():
    n = int(f.readline())
    D = [int(x) for x in f.readline().split()]
    param_polinom = [int(x) for x in f.readline().split()]
    precizia = int(f.readline())
    pc = float(f.readline())
    pm = float(f.readline())
    etape = int(f.readline())
    return n, D, param_polinom, precizia, pc, pm, etape

def generareCromozomi(l, n):
    #generez populatia initiala folosindu-ma de functia random din numpy
    #generez fiecare individ ca succesiune aleatoare de 0 si 1
    populatie = []
    for i in range(n):
        c = np.random.randint(2, size = l)
        populatie.append(c)
    return populatie

def codificare(D, cromozom):
    #intai transform cromozomul din baza 2 in baza 10
    bazaZece = 0
    putere = len(cromozom) - 1
    for i in cromozom:
        bazaZece += i * (2 ** putere)
        putere -= 1
    #aduc cromozomul in domeniul functiei
    cromozomCodificat = ((D[1] - D[0]) / (2 ** l - 1)) * bazaZece + D[0]

    #returnez cromozomul codificat
    return round(cromozomCodificat, precizia)

def probabilitate_selectie(i, fitness):
    #probabilitatea de selectie a cromozomului de pe pozitia i
    ps = fitness[i] / sum(fitness)
    return ps

def generare_intervale_selectie(populatie, fitness):
    prob_selectie = []
    interval_selectie = []
    last_ps = 0
    #capatul din stanga al intervalul este capatul din dreapta al ultimului interval
    #capatul din dreapata este capatul din stanga + probabilitatea
    for i in range(len(populatie)):
        ps = probabilitate_selectie(i, fitness)
        prob_selectie.append(ps)
        if len(interval_selectie) == 0:
            interval_selectie.append((0, ps))
            last_ps = ps
        else:
            ps += last_ps
            interval_selectie.append((last_ps, ps))
            last_ps = ps

    return interval_selectie, prob_selectie
#functie auxiliara pentru a ma ajuta sa scriu in fisier un cromozom
def cromozomeToString(cromozom):
    c = ""
    for j in cromozom:
        c += str(j)
    return c

#functie auxiliara pentru a scrie statisticile la fiecare pas
def writeStats(i, cromozom):
    c = cromozomeToString(cromozom)
    x = codificare(D, cromozom)
    f = param_polinom[0] * (x ** 3) + param_polinom[1] * (x ** 2) + param_polinom[2] * x + param_polinom[3]
    g.write(str(i + 2) + ": " + c + "   x = " + str(x) + "  f = " + str(f) + '\n')

#cautarea binara a intervalului corespunzator
#aflam mijlocul
#daca este intre capetele intervalului din mijloc atunci returnam mijlocul
#daca este mai mic decat capatul din stanga al intervalului din mijloc atunci cautarea se va face in stanga
#daca este mai mare decat capatul din dreapta al intervalului din mijloc atunci cautare se va face in dreapta
def binarySearch(intervale,  searched):
    if len(intervale) > 1:
        m = len(intervale) // 2 - 1
        if intervale[m][0] <= searched < intervale[m][1]:
            return m
        elif intervale[m][0] > searched:
            return binarySearch(intervale[:m], searched)
        else: return binarySearch(intervale[m + 1:], searched)
    else: return 0

#functie auxiliara pentru recombinarea a 2 cromozomi avand un punct de rupere generat anterior
def combineTwo(cromozom1, cromozom2, punct):
    c1, c2 = cromozom1[:punct] + cromozom2[punct:], cromozom2[:punct] + cromozom1[punct:]
    return c1, c2

#functie auxiliara pentru recombinarea a 3 cromozomi avand un punct de rupere generat anterior
def combineThree(cromozom1, cromozom2, cromozom3, punct):
    c1, c2, c3 = cromozom1[:punct] + cromozom2[punct:], cromozom2[:punct] + cromozom3[punct:], cromozom3[:punct] + cromozom1[punct:]
    return c1, c2, c3

#functia principala unde sunt generate si afisate noile populatii
def nextGen(populatie, pc, pm):
    newPopulation = []      #noua generatie

    #functia de fitness a fiecarui individ
    fitness = []
    for i in populatie:
        c = codificare(D, i)
        fit = param_polinom[0] * (c ** 3) + param_polinom[1] * (c ** 2) + param_polinom[2] * c + param_polinom[3]
        fitness.append(round(fit, 2))

    elita = fitness.index(max(fitness))  # gasim elementul elitist
    individ_elitist = populatie[elita]
    intervale_selectie, prob_selectie = generare_intervale_selectie(populatie, fitness)

    g.write("Probabilitati selectie\n")
    for i in range(len(prob_selectie)):
        g.write("Cromozom     " + str(i + 1) + "  probabilitate  " + str(prob_selectie[i]) + "\n")

    g.write("\nIntervale probabilitati selectie\n")
    for i in range(len(intervale_selectie)):
        if len(intervale_selectie[i]) > 0:
            if i == 0:
                g.write(str(intervale_selectie[i][0]) + " " + str(intervale_selectie[i][1]) + " ")
            else:
                g.write(str(intervale_selectie[i][1]) + " ")
            if (i - 1) % 3 == 0:
                g.write("\n")


    i = 0
    while i < len(populatie) - 1:
        # variabilele aleatoare pentru a vedea ce cromozomi participa la crossing over
        u1 = np.random.random()
        u2 = np.random.random()
        print("U1, u2", u1, u2)
        interval1 = binarySearch(intervale_selectie, u1)
        interval2 = binarySearch(intervale_selectie, u2)
        individ1 = populatie[interval1]
        individ2 = populatie[interval2]
        f1 = fitness[interval1]
        f2 = fitness[interval2]
        if f1 > f2:
            newPopulation.append(populatie[interval1])
            g.write(str(interval1 + 1) + "\n")
        else:
            newPopulation.append(populatie[interval2])
            g.write(str(interval1 + 1) + "\n")
        i += 1

    g.write("\nDupa selectie:\n")
    writeStats(-1, individ_elitist)
    for i in range(len(newPopulation)):
        writeStats(i, newPopulation[i])

    g.write("\nProbabilitatea de incrucisare " + str(pc) + "\n")

    #variabile aleatoare pentru crossing over
    co = np.random.rand(len(newPopulation))
    crossing_over = []      #indivizii care participa la crossing over
    not_crossing_over = []         #indivizii care nu participa
    #alegem cromozomii ce vor participa la crossing over
    for i in range(len(co)):
        c = ""
        for j in population[i]:
            c += str(j)
        if co[i] < pc:
            #selectan indivizii ce participa la crossing over
            crossing_over.append(newPopulation[i])
            g.write(str(i + 1) + ":  " + c + "   u = " + str(co[i]) + " < " + str(pc) + "  participa\n")
        else:
            not_crossing_over.append(newPopulation[i])
            g.write(str(i + 1) + ":  " + c + "   u = " + str(co[i]) + "\n")

    #verificam daca sunt cromozomi ce participa la crossing over
    if len(crossing_over) > 0:
        #generam punctul de rupere
        punct_rupere = np.random.randint(low = 0, high = len(crossing_over[0]) - 1)
        g.write("Punct rupere: " + str(punct_rupere) + "\n")
        #voi trata separat urmatoarele cazuri:
        #1. sunt doar 3 cromozomi ce participa la crossing over si ii incrucisez doar pe ei
        #2. sunt un numar impar de cromozomi ce participa la crossing over si ii incrucisez 2 cate 2 pana ajung la ultimii 3 pe care ii incrucisez intre ei
        #3. sunt un numar par de cromozomi ce participa la crosiing over si ii incrucisez 2 cate 2

        #dupa ce termin crossing over-ul noua populatie va fi formata din cromozomii ce nu au participat la crossing over
        #si cromozomii ce au participat si au fost incrucisati anterior
        if len(crossing_over) == 3:
            g.write("Recombinare dintre " + cromozomeToString(crossing_over[0]) + ", " + cromozomeToString(crossing_over[1]) + ", " + cromozomeToString(crossing_over[2]) + "\n")
            crossing_over[0], crossing_over[1], crossing_over[2] = combineThree(crossing_over[0], crossing_over[1], crossing_over[2], punct_rupere)
            g.write("Rezultat: " + cromozomeToString(crossing_over[0]) + ", " + cromozomeToString(crossing_over[1]) + ", " + cromozomeToString(crossing_over[2]) + "\n")
            newPopulation = not_crossing_over + crossing_over
        elif len(crossing_over) % 2 == 1 and len(crossing_over) > 1:
            last3 = crossing_over[(len(crossing_over) - 3):]
            crossing_over = crossing_over[:(len(crossing_over) - 3)]
            i = 0
            while i < len(crossing_over) - 1 :
                g.write("Recombinare dintre: " + cromozomeToString(crossing_over[i]) + " si " + cromozomeToString(crossing_over[i + 1]) + "\n")
                crossing_over[i], crossing_over[i + 1] = combineTwo(crossing_over[i], crossing_over[i + 1], punct_rupere)
                g.write("Rezultat: " + cromozomeToString(crossing_over[i]) + " si " + cromozomeToString(crossing_over[i + 1]) + "\n")
                i += 2
            g.write("Recombinare dintre " + cromozomeToString(last3[0]) + ", " + cromozomeToString(last3[1]) + ", " + cromozomeToString(last3[2]) + "\n")
            last3[0], last3[1], last3[2] = combineThree(last3[0], last3[1], last3[2], punct_rupere)
            g.write("Rezultat: " + cromozomeToString(last3[0]) + ", " + cromozomeToString(last3[1]) + ", " + cromozomeToString(last3[2]) + "\n")

            newPopulation = not_crossing_over + crossing_over + last3

        else:
            i = 0
            while i < len(crossing_over) - 1:
                g.write("Recombinare dintre: " + cromozomeToString(crossing_over[i]) + " si " + cromozomeToString(
                    crossing_over[i + 1]) + "\n")
                crossing_over[i], crossing_over[i + 1] = combineTwo(crossing_over[i], crossing_over[i + 1],
                                                                    punct_rupere)
                g.write("Rezultat: " + cromozomeToString(crossing_over[i]) + " si " + cromozomeToString(
                    crossing_over[i + 1]) + "\n")
                i += 2
            #adaugam indivizii de la crossing over la populatia totala
            newPopulation = not_crossing_over + crossing_over

    g.write("\nDupa recombinare\n")
    writeStats(-1, individ_elitist)
    for i in range(0, len(newPopulation)):
        writeStats(i, newPopulation[i])

    #pastrez cromozomii cu mutatii pentru a putea sa ii afisez
    cromozomi_cu_mutatii = []
    #mutatie rara
    for i in range(len(newPopulation)):
        #generez o probabilitate de mutatie
        prob_mutatie = np.random.rand()
        #daca probabilitatea generata este mai mica decat cea data atunci cromozomul va suferi o mutatie
        if prob_mutatie < pm:
            cromozomi_cu_mutatii.append(i + 1)
            #generez o gena random care va fi suferi mutatia
            gena = np.random.randint(low = 0, high = len(newPopulation[i]) - 1)
            #gena care sufera mutatia este transformata in inversul ei (din 1 in 0 sau din 0 in 1)
            newPopulation[i][gena] = 1 - newPopulation[i][gena]

    #scriu in fisier informatii
    g.write("\nProbabilitate de mutatie rara: " + str(pm) + "\n")
    if len(cromozomi_cu_mutatii) > 0:
        g.write("Au fost modificati cromozomii:\n")
        for i in cromozomi_cu_mutatii:
            g.write(str(i) + "\n")
    else:
        g.write("Nu au existat mutatii\n")

    g.write("Dupa mutatie:\n")
    writeStats(-1, individ_elitist)
    for i in range(len(newPopulation)):
        writeStats(i, newPopulation[i])

    #adaug individul elitist la populatia intermediara
    newPopulation.append(individ_elitist)
    x = codificare(D, newPopulation[0])
    maximum = param_polinom[0] * (x ** 3) + param_polinom[1] * (x ** 2) + param_polinom[2] * x + param_polinom[3]
    medie = maximum
    t = ()
    for i in range(1, len(newPopulation)):
        x = codificare(D, newPopulation[i])
        f = int(param_polinom[0]) * (x ** 3) + int(param_polinom[1]) * (x ** 2) + int(param_polinom[2]) * x + int(param_polinom[3])
        if f > maximum:
            maximum = f
            t = (maximum, x)
        medie += f
    maximum_evolution.append(t)
    g.write("Maximul: " + str(maximum) + "\nValoarea medie: " + str(medie/len(newPopulation)))
    return newPopulation

#main
n, D, param_polinom, precizia, pc, pm, etape = citire()

l = round(math.log((D[1] - D[0]) * (10 ** precizia), 2))

p = generareCromozomi(l, n)
population = []
#transform din lista de numpy array in lista de liste
for i in p:
    c = []
    for j in i:
        c.append(j)
    population.append(c)

#afisare date despre populatia initiala
g.write("Populatia initiala \n")

for i in range(len(population)):
    c = cromozomeToString(population[i])
    x = codificare(D, population[i])
    f = param_polinom[0] * (x ** 3) + param_polinom[1] * (x ** 2) + param_polinom[2] * x + param_polinom[3]
    g.write(str(i + 1) + ": " + c + "   x = " + str(x) + "  f = " + str(f) + '\n')

#pastrez evolutia maximului
maximum_evolution = []

#repet algoritmul de un anumit numari de ori (de etape)
for i in range(etape):
    g.write("\n\n\n")
    newGen = nextGen(population, pc, pm)
    population.clear()
    population = copy.deepcopy(newGen)

#scriu in fisier evolutia maximului
g.write("\nEvolutia maximului:\n")
for i in maximum_evolution:
    g.write(str(i) + "\n")

#afisez grafic evolutia maximului
plt.plot(maximum_evolution)
plt.show()
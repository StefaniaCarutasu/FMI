import citireGrafuri
g = open("graf.out", "w")
vfNecol = set()
def colorare():
    global vfNecol
    if len(vfNecol) <= 6:
        for nod in vfNecol:
            culVec = set()
            if nod in listAd:   
                for vec in listAd[nod]:
                    culVec.add(culoare[vec])
        
            culoare[nod] = min(set(culori) - culVec)
    else:
        for nod in vfNecol:
            if grad[nod] <= 5:
                x = nod
                if nod in listAd:
                    for vec in listAd[nod]: #scadem gradele vf vecine
                        grad[vec] -= 1
                break
        
        #apelam recursiv pt graful G - x
        vfNecol = vfNecol - {x}
        colorare()

        #colorare x cu o culoare diferita fata de cea a vecinilor
        culVec = set()
        for vec in listAd[x]:
            culVec.add(culoare[vec])
        
        culoare[x] = min(set(culori) - culVec)

nrVf, NrMu, listAd = citireGrafuri.citireList()
grad = [0] * (nrVf + 1)              #vector cu gardele nodurilor
for i in range(1, nrVf + 1):
    if i in listAd:
        grad[i] = len(listAd[i])
culoare = [0] * (nrVf + 1)            #vectori de culori pt noduri
culori = [1, 2, 3, 4, 5, 6]           #culori disponibile
vfNecol = set(range(1, nrVf + 1))     #varfurile necolorate ale grafului

colorare()

#afisare colorare graf
g.write("Graful se poate colora cu 6 culori:\n")
for i in range(1, nrVf + 1):
    g.write("{} - culoare {}\n".format(i, culoare[i]))
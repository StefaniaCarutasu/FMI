
s = "RLRRLLRLRL"
s = list(s)
stiva = []
j = 0
nrStringuri = 0
for i in s:
    if i == 'R':
        stiva.append(i)
        j = 0
    else:
        if j == 0:
            j = 1
            nrStringuri += 1
        stiva.pop()
print(nrStringuri)

nrStringuri = 0
c = 0
string = ""
for i in range(len(s)):
    if s[i] == "R":
        c += 1
        string += "R"
    else:
        string+="L"
        c -= 1
        if c == 0 and i != 0:
            nrStringuri += 1
            print(string)
            string = ""
print(nrStringuri)




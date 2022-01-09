f = open("input.txt", "r")
i = f.readlines()

s = set(i)
f.close()

g = open("input2.txt", "w")
g.write(str(len(s)) + " enitities")
g.writelines(s)
g.close()

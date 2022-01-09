f = open("Cod/Reference-Implementation/input.txt", 'w')


def generateFile(counter):
    phrase = "Line"
    for i in range(counter):
        newLine = phrase + str(i) + "\n"
        f.write(newLine)


generateFile(10000000)

def boxBlur(image):
    i = 0
    blurred = []
    while i <= len(image) - 3:
        j = 0
        blurredLine = []
        while j <= len(image[i]) - 3:
            cell = 0
            for k in range(i, i + 3):
                for l in range(j, j + 3):
                    cell += image[k][l]
            print(cell)
            blurredLine.append(cell // 9)
            j += 1
        blurred.append(blurredLine)
        i += 1
    return blurred
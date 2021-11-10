
import scipy.integrate as integrate
import math

infinit = float("Inf")
def userFunc(x):
    return math.exp( - (x ** 2) / 2)

def normalizationConstant(functie):

    integrated, tmp = integrate.quad(functie , -infinit, infinit)
    print(integrated)
    if integrated != 0:
        r = 1/integrated
        print(r)
    else:
        print("Nu se poate")

normalizationConstant(userFunc)
from Crypto.Cipher import AES

key = b'O cheie oarecare'
data = b'testtesttesttesttesttesttesttest'

cipher = AES.new(key, AES.MODE_ECB)
print(cipher.encrypt(data))

def lfsr():
    L = int(input("L = "))
    c = []
    for i in range(L):
        c.append(int(input("c = ")))
    s = []

    for i in range(L):
        s.append(int(input("s = ")))

    per = 0
    ok = True

    while ok:
        last_l_s = s[len(s) - L: len(s)]
        last_l_s.reverse()
        new_digit = sum([a * b for a, b in zip(c, last_l_s)]) % 2
        s.append(new_digit)
        per += 1

        if s[0: L] == s[len(s) - L: len(s)]:
            ok = False

    print(''.join([str(x) for x in s]))
    print(per)



lfsr()
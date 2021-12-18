import string
import secrets
import keyring

# este utila cand se doreste sugerearea unei parole sigure utilizatorului
def createPassword():
    alphabet = string.ascii_letters + string.digits + string.punctuation
    while True:
        password = ''.join(secrets.choice(alphabet) for i in range(15))
        if (any(c.islower() for c in password)
                and any(c.isupper() for c in password)
                and any(c.isdigit() for c in password) and any(c in ['.', '!', '$', '@'] for c in password)):
            break

    return password


def createURL():
    return secrets.token_urlsafe(32)


# pentru generarea unui token de acces sau a unei chei de criptare
def createHex():
    return secrets.token_hex(16)


# verifica daca parola introdusa de utilizator si cea reala se potrivesc
def compareSequences(s1, s2):
    return secrets.compare_digest(s1, s2)


def createFluidKey():
    return bin(secrets.randbits(100))


def setPassword(service, username, password):
    service_name = service
    keyring.set_password(service_name, username, password)


def getPassword(service_name, username):
    return keyring.get_password(service_name, username)


print(createPassword())
print(createURL())
print(createHex())
print(createFluidKey())

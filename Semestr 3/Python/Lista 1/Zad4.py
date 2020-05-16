def zaszyfruj(tekst, klucz):
    encoded = ""
    for letter in tekst:
        encoded += chr(ord(letter) ^ klucz)
    return encoded


def odszyfruj(szyfr, klucz):
    return zaszyfruj(szyfr, klucz)

print(odszyfruj(zaszyfruj("Python", 7), 7))
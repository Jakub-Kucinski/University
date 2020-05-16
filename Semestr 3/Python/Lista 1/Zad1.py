def vat_faktura(lista):
    vat = 0.23
    sum = 0.0

    for element in lista:
        sum += element

    return sum * vat


def vat_paragon(lista):
    vat = 0.23
    vat_from_lista = []
    sum = 0.0

    for element in lista:
        vat_from_lista.append(element * vat)

    for element in vat_from_lista:
        sum += element
    
    return sum


zakupy = [0.2, 0.5, 4.59, 6]
print(vat_faktura(zakupy))
print(vat_paragon(zakupy))
print(vat_faktura(zakupy) == vat_paragon(zakupy))
def kompresja(tekst):
    counter = 1
    result = ""
    tekst_len = len(tekst) - 1
    i = 0
    while i < tekst_len:
        if tekst[i] == tekst[i + 1]:
            counter += 1
        else:
            if counter > 1:
                result += str(counter)
            result += tekst[i]
            counter = 1
        i += 1
    if counter > 1:
        result += str(counter)
    result += tekst[i]
    return result


def dekompresja(tekst):
    result = ""
    tekst_len = len(tekst)
    i = 0
    while i < tekst_len:
        if tekst[i].isdigit():
            number_of_sign_in_str = ""
            while tekst[i].isdigit():
                number_of_sign_in_str += tekst[i]
                i += 1
            number_of_sign = int(number_of_sign_in_str)
            result += tekst[i] * number_of_sign
        else:
            result += tekst[i]
        i += 1
    return result


print(kompresja("aaabbcc"))
print(kompresja("abbbc"))
print(kompresja("abc"))
print(dekompresja(kompresja("aaabbcc")))
print(dekompresja(kompresja("abbbc")))
print(dekompresja(kompresja("abc")))
print(dekompresja("20a12b"))

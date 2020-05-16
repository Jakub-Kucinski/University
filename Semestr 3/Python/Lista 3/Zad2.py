def pierwiastek(n):
    i = 1
    while i * i <= n:
        i += 1
    return i - 1


for i in range(30):
    print(i, pierwiastek(i))

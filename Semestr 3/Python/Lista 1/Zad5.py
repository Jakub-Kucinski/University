def rozklad(n):
    tab = []
    i = 2
    while i * i <= n:
        if n % i == 0:
            counter = 0
            while n % i == 0:
                counter += 1
                n /= i
            tab.append((i, counter))
        i += 1
    if n != 1:
        tab.append((int(n), 1))
    return tab


print(rozklad(756))
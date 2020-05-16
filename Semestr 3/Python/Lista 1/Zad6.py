def digits(n):
    counter = 0
    while n > 0:
        n = n // 10
        counter += 1
    return counter


def printing_number(n, size):
    size_of_n = digits(n)
    print(" " * (size - size_of_n), n, end="")
    return
    

def tabliczka(x1, x2, y1, y2):
    max_size = digits(x2 * y2)
    print(" " * (max_size + 1), end="")
    for i in range(x1, x2 + 1):
        printing_number(i, max_size)
    print("")

    for i in range(y1, y2 + 1):
        printing_number(i, max_size)
        for j in range(x1, x2 + 1):
            printing_number(i * j, max_size)
        print("")


tabliczka(25, 31, 17, 34)
def romb(n):
    for i in range(1, n):
        print(" " * (n - i), end="")
        print("#" * (2 * i - 1))
    print("#" * (2 * n - 1))
    for i in range(1, n):
        print(" " * i, end="")
        print("#" * (2 * (n - i) - 1))


romb(4)
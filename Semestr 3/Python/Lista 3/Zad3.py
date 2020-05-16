def sudan(n, x, y):
    calc_sudans = {}

    def rec_sud(n, x, y):
        if n == 0:
            return x + y
        if y == 0:
            return x
        first_sudan = calc_sudans.get((n, x, y - 1), None)
        if first_sudan is None:
            first_sudan = rec_sud(n, x, y - 1)
            calc_sudans[(n, x, y - 1)] = first_sudan
        result = calc_sudans.get((n - 1, first_sudan, first_sudan + y), None)
        if result is None:
            result = rec_sud(n - 1, first_sudan, first_sudan + y)
            calc_sudans[(n - 1, first_sudan, first_sudan + y)] = result
        return result
    return rec_sud(n, x, y)


print(sudan(1, 3, 3))
print(sudan(1, 4, 3))
print(sudan(1, 4, 8))
print(sudan(1, 8, 4))

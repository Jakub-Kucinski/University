from functools import reduce
import timeit


def pierwsze_imperatywna(n):
    t = []
    k = 2
    while k <= n:
        i = 2
        is_prime = True
        while i < k:
            if k % i == 0:
                is_prime = False
            i += 1
        if is_prime:
            t.append(k)
        k += 1
    return t


def pierwsze_skladana(n):
    return [k for k in range(2, n + 1)
            if all([not (k % i == 0) for i in range(2, k)])]


def pierwsze_funkcyjna(n):
    if n < 2:
        return []
    return [2] + list(filter((lambda k: reduce((lambda x, y: x and y),
                      map((lambda i: not (k % i == 0)), range(2, k)))),
                      range(3, n+1)))


print(timeit.timeit("pierwsze_imperatywna(10000)",
      setup="from __main__ import pierwsze_imperatywna", number=1))
print(timeit.timeit("pierwsze_skladana(10000)",
      setup="from __main__ import pierwsze_skladana", number=1))
print(timeit.timeit("pierwsze_funkcyjna(10000)",
      setup="from __main__ import pierwsze_funkcyjna", number=1))
# print(pierwsze_imperatywna(20))
# print(pierwsze_skladana(20))
# print(pierwsze_funkcyjna(20))

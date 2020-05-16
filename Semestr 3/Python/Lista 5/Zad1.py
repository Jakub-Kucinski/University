from functools import reduce
import timeit


def doskonale_imperatywna(n):
    t = []
    k = 1
    while k <= n:
        sum = 0
        i = 1
        while i < k:
            if k % i == 0:
                sum += i
            i += 1
        if sum == k:
            t.append(k)
        k += 1
    return t


def doskonale_skladana(n):
    return [e for e in range(1, n + 1)
            if e == sum([k for k in range(1, e) if e % k == 0])]


def doskonale_funkcyjna(n):
    # return list(filter((lambda x: reduce((lambda a, b: a + b),
    # [k for k in range(1, x) if x % k == 0]) == x), range(2, n + 1)))
    return list(filter((lambda x: x == reduce((lambda a, b: a + b),
                list(filter((lambda k: x % k == 0), range(1, x))), 0)),
                range(1, n + 1)))


class IntIterator():
    def __init__(self, n):
        self.current = 1
        self.n = n

    def __next__(self):
        while self.current <= self.n:
            sum = 0
            i = 1
            while i < self.current:
                if self.current % i == 0:
                    sum += i
                i += 1
            if sum == self.current:
                self.current += 1
                return self.current - 1
            self.current += 1
        raise StopIteration()


class IntCollection():
    def __init__(self, n):
        self.n = n

    def __iter__(self):
        return IntIterator(self.n)


def testiter(n):
    for i in IntCollection(n):
        pass


print("     | imperatywna |  skladana | funkcyjna |  iterator")
for i in [10, 100, 1000]:
    t1 = timeit.timeit(f"doskonale_imperatywna({i})",
                       setup="from __main__ import doskonale_imperatywna",
                       number=1)
    t2 = timeit.timeit(f"doskonale_skladana({i})",
                       setup="from __main__ import doskonale_skladana",
                       number=1)
    t3 = timeit.timeit(f"doskonale_funkcyjna({i})",
                       setup="from __main__ import doskonale_funkcyjna",
                       number=1)
    t4 = timeit.timeit(f"testiter({i})",
                       setup="from __main__ import testiter",
                       number=1)
    print(f"{i:4} | {t1:11.4} | {t2:9.4} | {t3:9.4} | {t4:9.4}")


# for i in IntCollection(10000):
#     print(i)
# print(timeit.timeit("doskonale_imperatywna(10000)",
#       setup="from __main__ import doskonale_imperatywna", number=1))
# print(timeit.timeit("doskonale_skladana(10000)",
#       setup="from __main__ import doskonale_skladana", number=1))
# print(timeit.timeit("doskonale_funkcyjna(10000)",
#       setup="from __main__ import doskonale_funkcyjna", number=1))
# # print(doskonale_imperatywna(10000))
# print(doskonale_skladana(10000))
# print(doskonale_funkcyjna(10000))

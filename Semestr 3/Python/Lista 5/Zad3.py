import itertools


def picture(H, V):
    len_of_H = len(H)
    len_of_V = len(V)
    iterator = itertools.product([0, 1], repeat=len_of_H * len_of_V)
    for iter in iterator:
        # print(iter)
        is_solution = True
        for j in range(len_of_V):
            if sum((iter[n + j * len_of_H] for n in range(len_of_H))) != V[j]:
                is_solution = False
                break
        if is_solution:
            for j in range(len_of_H):
                if sum((iter[j + n * len_of_H] for n in range(len_of_V))) \
                   != H[j]:
                    is_solution = False
                    break
        if is_solution:
            t = []
            for j in range(len_of_V):
                t.append([iter[n + j * len_of_H] for n in range(len_of_H)])
            return t
    return "Brak rozwiazania"


def picture_printing(picture):
    width = len(picture)
    hight = len(picture[0])
    for i in range(hight):
        for j in range(width):
            if picture[i][j] == 1:
                print("X", end="")
            else:
                print(" ", end="")
        print("")


picture_printing(picture((2, 1, 3, 1), (1, 3, 1, 2)))

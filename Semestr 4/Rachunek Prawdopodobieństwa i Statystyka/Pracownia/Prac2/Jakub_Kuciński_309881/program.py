import numpy as np
import math

def get_data():
    f = open("Ned.txt", "r")
    line = f.readline()
    T = []
    while line:
        line = f.readline()
        if line:
            T.append(line)

    for i in range(len(T)):
        T[i] = T[i][0:-1]
    for i in range(len(T)):
        T[i] = float(int(T[i]))

    f.close()
    f = open("Swe.txt", "r")
    line = f.readline()
    S = []
    while line:
        line = f.readline()
        if line:
            S.append(line)

    for i in range(len(S)):
        S[i] = S[i][0:-1]
    for i in range(len(S)):
        S[i] = float(int(S[i]))
    f.close()
    return T, S

def print_results(start_x, start_y, min_dni, T):
    print("Współczynnik korelacji", T[0],
          "\nMinimalna liczba dni:", min_dni,
          "\nMinimalny początek dla Holandii:", start_x,
          "\nMinimalny początek dla Szwecji:", start_y,
          "\nLiczba dni w obliczonym współczynniku:", T[3],
          "\nPoczątek dla Holandii:", T[1],
          "\nPoczątek dla Szwecji:", T[2], "\n")

def correlation_coefficient(X, Y):
    n = len(X)
    sum_xy = sum(X * Y)
    sum_x = sum(X)
    sum_y = sum(Y)
    sum_xx = sum(X ** 2)
    sum_yy = sum(Y ** 2)
    EXY = sum_xy / n
    EX = sum_x / n
    EY = sum_y / n
    EXX = sum_xx / n
    EYY = sum_yy / n
    VX = EXX - EX ** 2
    VY = EYY - EY ** 2
    COVXY = EXY - EX * EY
    return COVXY / math.sqrt(VX * VY)

def find_best_correlation(X, Y, start_x, start_y, min_days):
    n_x = len(X)
    n_y = len(Y)
    max_days = 0
    max_cov = -1.0
    start_x_of_max_cov = 0
    start_y_of_max_cov = 0
    size_of_max_cov = 0
    if n_x - start_x > n_y - start_y:
        max_days = n_y - start_y
    else:
        max_days = n_x - start_x
    for size in range(min_days, max_days):
        for i in range(start_x, n_x):
            if i + size >= n_x:
                break
            for j in range(start_y, n_y):
                if j + size >= n_y:
                    break
                cov = correlation_coefficient(X[i:i+size], Y[j:j+size])
                if cov > max_cov:
                    max_cov = cov
                    start_x_of_max_cov = i
                    start_y_of_max_cov = j
                    size_of_max_cov = size
    return max_cov, start_x_of_max_cov, start_y_of_max_cov, size_of_max_cov


def find_best_correlation_till_end(X, Y, start_x, start_y, min_days):
    n_x = len(X)
    n_y = len(Y)
    size = 0
    max_cov = -1.0
    start_x_of_max_cov = 0
    start_y_of_max_cov = 0
    size_of_max_cov = 0
    for i in range(start_x, n_x):
        for j in range(start_y, n_y):
            if n_x - i > n_y - j:
                size = n_y - j
            else:
                size = n_x - i
            if size < min_days:
                break
            cov = correlation_coefficient(X[i:i+size], Y[j:j+size])
            if cov > max_cov:
                max_cov = cov
                start_x_of_max_cov = i
                start_y_of_max_cov = j
                size_of_max_cov = size
    return max_cov, start_x_of_max_cov, start_y_of_max_cov, size_of_max_cov


# Obliczanie współczynnika korelacji zachorowań dla Holandii oraz Szwecji

X, Y = get_data()
X = np.asarray(X, dtype=np.float64)
Y = np.asarray(Y, dtype=np.float64)

print("\n")
# Maksymalna korelacja dla przynajmniej 20 dni
# Od pierwszych zachorowań
print_results(0, 0, 20, find_best_correlation(X, Y, 0, 0, 20))
# Od pierwszego dnia z ponad 50 zachorowaniami
print_results(9, 9, 20, find_best_correlation(X, Y, 9, 9, 20))
# Od pierwszego dnia z ponad 100 zachorowaniami
print_results(13, 14, 20, find_best_correlation(X, Y, 13, 14, 20))

print("\n")

# Analogicznie, ale dla przynajmniej 30 dni
print_results(0, 0, 30, find_best_correlation(X, Y, 0, 0, 30))
print_results(9, 9, 30, find_best_correlation(X, Y, 9, 9, 30))
print_results(13, 14, 30, find_best_correlation(X, Y, 13, 14, 30))

print("\n")

# Dla przynajmniej 40 dni
print_results(0, 0, 40, find_best_correlation(X, Y, 0, 0, 40))
print_results(9, 9, 40, find_best_correlation(X, Y, 9, 9, 40))
print_results(13, 14, 40, find_best_correlation(X, Y, 13, 14, 40))

print("\n")
# Maksymalna korelacja dla przynajmniej 20 dni
# Od pierwszych zachorowań
print_results(0, 0, 20, find_best_correlation_till_end(X, Y, 0, 0, 20))
# Od pierwszego dnia z ponad 50 zachorowaniami
print_results(9, 9, 20, find_best_correlation_till_end(X, Y, 9, 9, 20))
# Od pierwszego dnia z ponad 100 zachorowaniami
print_results(13, 14, 20, find_best_correlation_till_end(X, Y, 13, 14, 20))

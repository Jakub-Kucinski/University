import numpy as np

def get_data(file):
    f = open(file, "r")
    line = f.readline()
    T = []
    while line:
        line = f.readline()
        if line:
            T.append(line.split(";")[1:])

    for line in T:
        line[-1] = line[-1][0:-1]
    for line in T:
        for i in range(len(line)):
            line[i] = float(line[i])
    f.close()
    return T

def r1(x, y, T):
    sum_x = sum(T[:, x])
    sum_y = sum(T[:, y])
    sum_xy = sum(T[:, x] * T[:, y])
    sum_xx = sum(T[:, x] ** 2)
    n = len(T[:, x])
    a_nominator = sum_xy  - sum_x * sum_y / n
    a_denominator = sum_xx - sum_x * sum_x / n
    a = a_nominator / a_denominator
    b = sum_y / n - a * sum_x / n
    # print(sum_x, sum_y, sum_xy, sum_xx, n, a_nominator, a_denominator, a, b)
    return a, b

def r2(x, y, z, T):
    n = len(T[:, x])
    scalar_11 = n
    scalar_1x = sum(T[:, x])
    scalar_1y = sum(T[:, y])
    scalar_1z = sum(T[:, z])
    scalar_xx = sum(T[:, x] ** 2)
    scalar_xy = sum(T[:, x] * T[:, y])
    scalar_xz = sum(T[:, x] * T[:, z])
    scalar_yy = sum(T[:, y] ** 2)
    scalar_yz = sum(T[:, y] * T[:, z])
    matrix_T = np.array([[scalar_11, scalar_1x, scalar_1y],
                         [scalar_1x, scalar_xx, scalar_xy],
                         [scalar_1y, scalar_xy, scalar_yy]])
    vector_Z = np.array([scalar_1z, scalar_xz, scalar_yz])
    matrix_B = np.linalg.solve(matrix_T, vector_Z)
    return matrix_B


def r3(x, y, z, T):
    n = len(T[:, x])
    ones = np.array([np.ones(n, dtype=np.float64)])
    print(ones)
    matrix_1XY = np.concatenate((ones.T, T[:, [x, y]]), axis=1)
    print(ones.T)
    print( T[:, [x, y]])
    print(matrix_1XY)
    vector_Z = matrix_1XY.T @ T[:, z]
    matrix_T = matrix_1XY.T @ matrix_1XY
    vector_B = np.linalg.solve(matrix_T, vector_Z)
    return vector_B

T = get_data("klimat.csv")

T = np.asarray(T, dtype=np.float64)
print('   Latitude    ', 'Longitude  ', 'Precipitation', 'Temperature', 'Altitude')
print(T)
latitude = 0
longitude = 1
precipitation = 2
temperature = 3
altitude = 4

# for i in range(len(T[:, temperature])):
#     print("{" + str(T[i, temperature]) + "," + str(T[i, altitude]) + "},", end="")

# for i in range(len(T[:, temperature])):
#     print(T[i, altitude], end=" ")

print("Task 1:")
a, b = r1(altitude, temperature, T)
print("y =", b, "+", a, "x")

print("Task 2:")
B = r2(latitude, longitude, temperature, T)
print("z =", B[0], "+", B[1], "x +", B[2], "y")

print("Task 2:")
B = r3(latitude, longitude, temperature, T)
print("z =", B[0], "+", B[1], "x +", B[2], "y")


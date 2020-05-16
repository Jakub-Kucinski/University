import numpy as np
n = 200000
t = np.random.permutation(n)
p = np.random.permutation(n)


f = open("t1.txt", "w+")
f.write("200000\n")
for i in range(n):
    s = "" + str(t[i]) + " " + str(p[i]) + "\n"
    f.write(s)
     
f.close() 
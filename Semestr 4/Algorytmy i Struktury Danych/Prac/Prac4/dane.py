import random

N = random.randrange(0, 1000000)
zakres = random.randrange(0, 1000000000)
k = random.randrange(0, N)

f = open("t2.txt", "w+")
tekst = "" + str(N) + " " + str(k) + "\n"
f.write(tekst)

for i in range(N):
    s = "" + str(random.randrange(zakres)) + " "
    f.write(s)

f.close()
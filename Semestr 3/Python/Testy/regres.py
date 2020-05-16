import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
# T = [0, 10, 20, 30, 40, 80, 90, 95]
# S = [68.0, 67.1, 66.4, 65.6, 64.6, 61.8, 61.0, 60.0]
# print(sum(T))
# print(sum([e * e for e in T]))
# print(sum(S))
# print(sum([T[i] * S[i] for i in range(len(T))]))
# print(8 * 26525 - 365 * 365)
# print(514.5 * 26525 - 22685 * 365)
# print(5367087.5 / 78975)
# print(26525 * 514.5 - 365 * 22685)
# print(-365 * 514.5 + 8 * 22685)
# adbc = 1/(8*26525 - 365*365)
# a = (26525 * 514.5 - 365 * 22685)/(8*26525 - 365*365)
# b = (-365 * 514.5 + 8 * 22685)/(8*26525 - 365*365)
# for i in T:
#     print(b * i + a)
# print(5367087.5 / 78975)
# print(8 * 22685 - 365 * 514.5)


fig = plt.figure()
ax = plt.axes(xlim=(-2, 2), ylim=(-2, 2))
xdata, ydata = [], []
line, = ax.plot([], [])


def init():
    line.set_data([], [])
    return line,


def animate(i):
    t = 0.01 * i
    x = np.sin(1 * t + np.pi / 2.0)
    y = np.sin(1 * t)
    xdata.append(x)
    ydata.append(y)
    line.set_data(xdata, ydata)
    return line,


ani = FuncAnimation(fig, animate, init_func=init, frames=50, interval=50, blit=True)
plt.show()
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


live = 255
dead = 0


# def init():
#     network = np.random.choice((0, 255), N * N, p=[0.90, 0.10]).reshape(N, N)
#     img.set_data(network)
#     return img,


def animate(num_of_frame, img, network, N):
    new_net = network.copy()
    for i in range(N):
        for j in range(N):
            alive_neighbours = int((network[(i + 1) % N, (j + 1) % N] +
                                   network[(i + 1) % N, j % N] +
                                   network[(i + 1) % N, (j - 1) % N] +
                                   network[i % N, (j - 1) % N] +
                                   network[(i - 1) % N, (j - 1) % N] +
                                   network[(i - 1) % N, j % N] +
                                   network[(i - 1) % N, (j + 1) % N] +
                                   network[i % N, (j + 1) % N])/255)
            if network[i, j] == dead:
                if alive_neighbours == 3:
                    new_net[i, j] = live
            else:
                if (alive_neighbours < 2) or (alive_neighbours > 3):
                    new_net[i, j] = dead
    network[:] = new_net[:]
    img.set_data(network)
    return img,


def game_of_life():
    fig = plt.figure()
    ax = plt.axes()
    N = 100
    # network = np.zeros(N * N).reshape(N, N)
    network = np.random.choice((0, 255), N*N, p=[0.90, 0.10]).reshape(N, N)
    img = ax.imshow(network)

    FuncAnimation(fig, animate, frames=50, fargs=(img, network, N,),
                  interval=50, blit=True)
    plt.show()


game_of_life()

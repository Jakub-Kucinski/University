import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import numpy as np


def make_more_colorful(img, scale):
    dominant = np.zeros(img.shape, dtype="float32")
    scale = scale/9.0
    dominant[:, :, :] += scale * img[:, :, :]
    dominant[:, 0:img.shape[1]-1, :] += scale * img[:, 1:img.shape[1], :]
    dominant[:, 1:img.shape[1], :] += scale * img[:, 0:img.shape[1]-1, :]
    dominant[0:img.shape[0]-1, :, :] += scale * img[1:img.shape[0], :, :]
    dominant[1:img.shape[0], :, :] += scale * img[0:img.shape[0]-1, :, :]
    dominant[0:img.shape[0]-1, 0:img.shape[1]-1, :] += scale * img[1:img.shape[0], 1:img.shape[1], :]
    dominant[0:img.shape[0]-1, 1:img.shape[1], :] += scale * img[1:img.shape[0], 0:img.shape[1]-1, :]
    dominant[1: img.shape[0], 1:img.shape[1], :] += scale * img[0:img.shape[0]-1, 0:img.shape[1]-1, :]
    dominant[1: img.shape[0], 0:img.shape[1]-1, :] += scale * img[0:img.shape[0]-1, 1:img.shape[1], :]

    more_colorful = img.copy()
    more_colorful[:, :, :] += dominant[:, :, :]
    return more_colorful


def make_more_grey(img, scale):
    more_grey = img.copy()
    more_grey[:, :, 0] = (1.0 - scale) * img[:, :, 0] + scale * (
            0.299 * img[:, :, 0] + 0.587 * img[:, :, 1] + 0.114 * img[:, :, 2])
    more_grey[:, :, 1] = (1.0 - scale) * img[:, :, 1] + scale * (
            0.299 * img[:, :, 0] + 0.587 * img[:, :, 1] + 0.114 * img[:, :, 2])
    more_grey[:, :, 2] = (1.0 - scale) * img[:, :, 2] + scale * (
            0.299 * img[:, :, 0] + 0.587 * img[:, :, 1] + 0.114 * img[:, :, 2])
    return more_grey


img = mpimg.imread('laszielony.png')
fig = plt.figure()
a = fig.add_subplot(2, 2, 1)
imgplot = plt.imshow(img)
a.set_title('Original')

a = fig.add_subplot(2, 2, 2)
new = make_more_colorful(img, 1.0/2.0)
imgplot = plt.imshow(new)
a.set_title('Colorful')

a = fig.add_subplot(2, 2, 3)
new = make_more_grey(img, 2.0/3.0)
imgplot = plt.imshow(new)
a.set_title('Greyer')
plt.show()


# 0.299 R + 0.587 G + 0.114 B

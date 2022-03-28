from matplotlib.pyplot import axis
import matplotlib.pyplot as plt
import numpy as np
import random
import cv2

RGB_PALETTE = np.array([[0., 0., 0.],
[0., 0., 1.],
[0. ,1. ,0.],
[0. ,1. ,1.],
[1. ,0. ,0.],
[1. ,0. ,1.],
[1. ,1. ,0.],
[1. ,1. ,1.]])

def colorFit(colors, palette):
    return palette[np.argmin(np.linalg.norm(colors-palette,axis=1))]

def randomDithering(sourceIm):
    image = sourceIm.copy()
    height, width = image.shape[:2]

    for y in range(width-1):
        for x in range(height-1):
            if(random.random()<image[x,y]):
                image[x,y]=1
            else:
                image[x,y]=0
    
    
    plt.imshow(image)
    plt.show()
    return image

img1 = plt.imread('0009.png')[:,:,0]


x=8
c = np.linspace(0,1,x).reshape(x,1)

#plt.imshow(img1)
randomDithering(img1)

colorFit(c, RGB_PALETTE)

import cv2 
import numpy as np
import matplotlib.image as mpimg
import matplotlib.pyplot as plt

def nearest_neighbour(im, wsp):
    height, width= im.shape[:2]
    n_height = int(height * wsp)
    n_width = int(width * wsp)

    newIm = np.zeros((n_height, n_width, 3), dtype=np.uint8)

    newY = np.linspace(0,height-1,n_height)
    newX = np.linspace(0,width-1,n_width)

    for i in range(n_height):
        pxY = round(newY[i])
        for j in range(n_width):
            pxX = round(newX[j])
            newIm[i][j] = im[pxY][pxX]

    return newIm


def interp(im, wsp):
    height, width= im.shape[:2]
    n_height = int(height * wsp)
    n_width = int(width * wsp)


    x_ratio = float(width -1)/(n_width-1) if width>1 else 0
    y_ratio = float(height -1)/(n_height-1) if height>1 else 0


    newIm = np.zeros((n_height, n_width, 3), dtype=np.uint8)

    newY = np.linspace(0,height-1,n_height)
    newX = np.linspace(0,width-1,n_width)

    for i in range(n_height):
        Q_y = np.floor(newY[i])
        for j in range(n_width):
            Q_x = np.floor(newX[j])

            x = (int)(newY-Q_x)
            y = (int)(newX-Q_y)

            newIm[i][j] = im[Q_y][Q_x]*(1-x)*(1-y)+img[Q_y+1][Q_x]*x*(1-y)+img[Q_y][Q_x+1]*(1-x)*y+img[Q_y+1][Q_x+1]*x*y

    return newIm



    # r = height/n_height

    # for i in range(n_width):
    #     for j in range(n_height):
    #         rx = np.Floor(i*r)
    #         ry = np.Floor(j*r)

    #         #print(rx," ",ry,"\n")

    
#img=mpimg.imread('0002.jpg')
img= np.zeros((3,3,3), dtype=np.uint8)
img[1,1,:]=255

imgplot=plt.imshow(img)
plt.show()
plt.imshow(nearest_neighbour(img, 4))
plt.show()
plt.imshow(interp(img,4))
plt.show()

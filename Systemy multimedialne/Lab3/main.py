import numpy as np
import matplotlib.pyplot as plt
import math as m

def f(img, x, y, Q_y, Q_x):
    return img[Q_y][Q_x]*(1-x)*(1-y)+img[Q_y+1][Q_x]*x*(1-y)+img[Q_y][Q_x+1]*(1-x)*y+img[Q_y+1][Q_x+1]*x*y

def NN(img, scale):
    new_width = int(img.shape[1]*scale)
    new_height = int(img.shape[0]*scale)
    
    height_grid = np.linspace(0, img.shape[0] - 1, new_height)
    width_grid = np.linspace(0, img.shape[1] - 1, new_width)
    
    new_img = np.zeros((new_height, new_width, 3), dtype=np.uint8)
    
    for row in range(new_height):
        est_y = round(height_grid[row])
        for col in range(new_width):
            est_x = round(width_grid[col])
            new_img[row][col] = img[est_y][est_x]
            
            
    return new_img


def Interpolacja_dwuliniowa(img, scale):
    new_width = int(img.shape[1]*scale)
    new_height = int(img.shape[0]*scale)
    
    height_grid = np.linspace(0, img.shape[0] - 1, new_height)
    width_grid = np.linspace(0, img.shape[1] - 1, new_width)
    
    new_img = np.zeros((new_height, new_width, 3), dtype=np.uint8)
    
    for row in range(new_height - 1):
        Q_y = m.floor(height_grid[row])
        for col in range(new_width - 1):
            Q_x = m.floor(width_grid[col])
            # print(img[Q_y, Q_x, :])
            # print(img[Q_y, Q_x+1, :])
            # print(img[Q_y+1, Q_x, :])
            # print(img[Q_y+1, Q_x+1, :])
            # print(height_grid[row] - Q_x, width_grid[col] - Q_y)
            x = height_grid[row] - Q_x
            y = width_grid[col] - Q_y
            new_img[row, col] = f(img, y, x, Q_y, Q_x)
            
            
    return new_img
    
    

def main():
    img= np.zeros((3,3,3),dtype=np.uint8)
    img[1,1,:] = 255
    #new_img = NN(img, 5)
    new_img = Interpolacja_dwuliniowa(img, 5)
    plt.imshow(new_img)
    plt.show()
    
main()
    
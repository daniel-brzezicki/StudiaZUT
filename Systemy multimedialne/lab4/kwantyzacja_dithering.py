from matplotlib.pyplot import axis
import matplotlib.pyplot as plt
import numpy as np
import random
import cv2

def colorFit(colors, palette):
    return palette[np.argmin(np.linalg.norm(palette-colors,axis=1))]

def checkImage(sourceIm):
    if(sourceIm.dtype==np.uint8):
        image= sourceIm.copy()/255
    else:
        image = sourceIm.copy()
    return image


def quantize(sourceIm, palette):
    image = checkImage(sourceIm)

    height, width = image.shape[:2]

    for y in range(width):
        for x in range(height):
            image[x,y] = colorFit(image[x,y], palette)
    return image


def randomDithering(sourceIm):
    sourceIm = checkImage(sourceIm)
    image = sourceIm.copy()
    layer=1
    if len(image.shape) < 3:
        height, width = image.shape[:2]
    else:
        height, width, layer = image.shape[:3]

    for y in range(width-1):
        for x in range(height-1):
            if(random.random()<image[x,y]):
                image[x,y]=1
            else:
                image[x,y]=0
    
    return image

def organizedDithering(sourceIm, palette):
    sourceIm = checkImage(sourceIm)

    image= sourceIm.copy()
    height, width = image.shape[:2]


    M = np.array([
        [0, 8, 2, 10],
        [12, 4, 14, 6],
        [3, 11, 1, 9],
        [15, 7, 13, 5]
        ])

    n = M.shape[0]
    mPre = (M+1)/n**2-0.5

    for y in range(width):
        for x in range(height):
            image[x,y]=colorFit(image[x,y] + mPre[y%n,x%n], palette)

    return image

def fdHelper(x,y, width,height):
    if(x in range(width) and y in range(height)):
        return True
    return False

def floydDithering(sourceIm, palette):
    sourceIm = checkImage(sourceIm)

    image= sourceIm.copy()
    width, height = image.shape[:2]

    for x in range(width):
        for y in range(height):
            oldpixel = image[x,y].copy()
            newpixel = colorFit(oldpixel, palette)
            image[x,y] = newpixel
            quant_error = oldpixel - newpixel

            if(fdHelper(x+1,y,width,height)):
                image[x + 1,y    ] = image[x + 1,y    ] +quant_error * 7 / 16
            if(fdHelper(x-1,y+1,width,height)):
                image[x - 1,y + 1] = image[x - 1,y + 1] + quant_error * 7 / 16
            if(fdHelper(x,y+1,width,height)):
                image[x    ,y + 1] = image[x    ,y + 1] + quant_error * 7 / 16
            if(fdHelper(x+1,y+1,width,height)):
                image[x + 1,y + 1] = image[x + 1,y + 1] + quant_error * 7 / 16

    for x in range(width):
        for y in range(height):
            image[x,y]=colorFit(image[x,y],palette)

    return image


def TestImage(sourceIm,palette):
    image = sourceIm.copy()

    layer=0
    if len(image.shape) < 3:
        height, width = image.shape[:2]
    else:
        height, width, layer = image.shape[:3]

    cm=None
    if (layer < 3):
        cm="gray"

    #original
    # plt.title('Original image')
    # plt.imshow(image,cmap=cm)
    # plt.show()

    # plt.title('Quantize')
    # q = quantize(image,palette)
    # plt.imshow(q,cmap=cm)
    # plt.show()

    # if(layer < 3 and len(palette)==2):
    #     plt.title('Random Dithering')
    #     rd = randomDithering(image)
    #     plt.imshow(rd,cmap=cm)
    #     plt.show()

    # plt.title('Organized Dithering')
    # od = organizedDithering(image,palette)
    # plt.imshow(od,cmap=cm)
    # plt.show()

    plt.title('Floyd-Steinberg Dithering')
    fd = floydDithering(image,palette)
    plt.imshow(fd,cmap=cm)
    plt.show()
        


RGB8Bit = np.array([
    [0., 0., 0.],
    [0., 0., 1.],
    [0. ,1. ,0.],
    [0. ,1. ,1.],
    [1. ,0. ,0.],
    [1. ,0. ,1.],
    [1. ,1. ,0.],
    [1. ,1. ,1.]
    ])

RGB16Bit = np.array([
    [0, 0, 0],
    [0, 1, 1],
    [0, 0, 1],
    [1, 0, 1],
    [0, 0.5, 0],
    [0.5, 0.5, 0.5],
    [0, 1, 0],
    [0.5, 0, 0],
    [0, 0, 0.5],
    [0.5, 0.5, 0],
    [0.5, 0, 0.5],
    [1, 0, 0],
    [0.75, 0.75, 0.75],
    [0, 0.5, 0.5],
    [1, 1, 1],
    [1, 1, 0]
    ])

grey1Bit = np.linspace(0, 1, 2).reshape((2, 1))
grey2Bit = np.linspace(0, 1, 4).reshape((4, 1))
grey4Bit = np.linspace(0, 1, 8).reshape((8, 1))

images = [
    '0001.jpg','0002.jpg','0003.jpg','0004.png',
    '0005.tif','0006.tif','0007.tif','0008.png',
    '0009.png','0010.jpg','0011.jpg','0012.jpg',
    '0012.jpg','0013.jpg','0014.jpg','0015.jpg',
    '0016.jpg'
]

# greyImages = [images[6], images[7]]
# for greyImage in greyImages:
#    TestImage(plt.imread(greyImage),grey4Bit)

# for greyImage in greyImages:
#     TestImage(plt.imread(greyImage),grey2Bit)

# for greyImage in greyImages:
#     TestImage(plt.imread(greyImage),grey4Bit)


rgbImages = [images[4],images[13]]
for rgbImage in rgbImages:
    TestImage(plt.imread(rgbImage),RGB8Bit)

# own = np.array([
#     [137,139,142],#zol
#     [58,64,70], #z
#     [196,191,178],
#     [89,94,102],
#     [180,188,185],
#     [172,172,174],
#     [205,196,182],
#     [33,35,36]
#     ])


# TestImage(plt.imread(images[11]),RGB8Bit)


# im = quantize(img3,RGB_PALETTE)
# plt.imshow(im)
# plt.show()

# im = randomDithering(img3)
# plt.imshow(im)
# plt.show()


# im = organizedDithering(img3,RGB_PALETTE)
# plt.imshow(im)
# plt.show()


# im = floydDithering(img3,RGB_PALETTE)
# plt.imshow(im)
# plt.show()



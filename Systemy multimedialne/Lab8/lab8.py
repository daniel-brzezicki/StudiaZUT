import scipy.fftpack
import numpy as np
import cv2
import matplotlib.pyplot as plt


def convertToYCrCb(image):
    return cv2.cvtColor(image,cv2.COLOR_RGB2YCrCb).astype(int)

def convertToRGB(image):
    return cv2.cvtColor(image.astype(np.uint8),cv2.COLOR_YCrCb2RGB)

def dct2(a):
    return scipy.fftpack.dct(scipy.fftpack.dct( a.astype(float), axis=0, norm='ortho' ), axis=1, norm='ortho' )

def idct2(a):
    return scipy.fftpack.idct(scipy.fftpack.idct( a.astype(float), axis=0 , norm='ortho'), axis=1 , norm='ortho')



class Data:
    YCrCb=[]
    #shape = (0,0,0)
    pass

def compress(image):
    data = Data()
    data.YCrCb=convertToYCrCb(image)
    return data

def decompress(data):
    image = convertToRGB(data.YCrCb)
    return image


image = cv2.imread('zyrafa.jpg')
plt.imshow(image)
plt.title('Original')
plt.show()


compressed= compress(image)
decompressed = decompress(compressed)
plt.imshow(decompressed)
plt.title('Decompressed')
plt.show()


#YCrCb=cv2.cvtColor(RGB,cv2.COLOR_RGB2YCrCb).astype(int)
#RGB=cv2.cvtColor(YCrCb.astype(np.uint8),cv2.COLOR_YCrCb2RGB)
# def zigzag(A):
#     template= n= np.array([
#             [0,  1,  5,  6,  14, 15, 27, 28],
#             [2,  4,  7,  13, 16, 26, 29, 42],
#             [3,  8,  12, 17, 25, 30, 41, 43],
#             [9,  11, 18, 24, 31, 40, 44, 53],
#             [10, 19, 23, 32, 39, 45, 52, 54],
#             [20, 22, 33, 38, 46, 51, 55, 60],
#             [21, 34, 37, 47, 50, 56, 59, 61],
#             [35, 36, 48, 49, 57, 58, 62, 63],
#             ])
#     if len(A.shape)==1:
#         B=np.zeros((8,8))
#         for r in range(0,8):
#             for c in range(0,8):
#                 B[r,c]=A[template[r,c]]
#     else:
#         B=np.zeros((64,))
#         for r in range(0,8):
#             for c in range(0,8):
#                 B[template[r,c]]=A[r,c]
#     return B

# print(zigzag())
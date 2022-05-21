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



def chromaSubsample(data, params):
    J, a, b = list(map(int, params.split(':')))
    y,x = data.shape
    if J==a and a == b:
        return data

    result=np.empty((y, int(x/2)))
    if params=="4:2:2":
        for _y in range(0,y):
            for _x in range(0,x,2):
                result[_y][int(_x/2)]=data[_y][_x]
    
    return result

def chromaDesubsample(data, params):
    J, a, b = list(map(int, params.split(':')))
    y,x = data.shape
    if J==a and a == b:
        return data

    result=np.empty((y, x*2))
    if params=="4:2:2":
        for _y in range(0,y):
            for _x in range(0,x,2):
                result[_y][_x*2]=data[_y][_x]
                result[_y][_x*2+1]=data[_y][_x]

    return result    

def compress(SourceIm,params, tab):
    #data.YCrCb=convertToYCrCb(image)
    sampled=chromaSubsample(SourceIm,params)
    sampled = sampled.astype(int)-128

    dct = scipy.fftpack.dct( scipy.fftpack.dct(sampled.astype(float), axis=0, norm='ortho' ), axis=1, norm='ortho' )
    y,x = sampled.shape
    result=np.zeros(y*x)
    idx=0
    for _y in range(0,y,8):
        for _x in range(0,x,8):
            toZig=dct[_y:_y+8,_x:_x+8]
            tmp=zigzag(toZig)
            result[idx:idx+64]=np.round(tmp/tab.flatten()).astype(int)
            idx+=64
    return result


   

def decompress(data,params,tab):
    y,x=data.shape
    if params == "4:4:4":
        result=np.zeros(
            int(np.sqrt(y)),
            int(np.sqrt(y))
        )
    else:
        result=np.zeros(
            int(np.sqrt(y*2)),
            int(np.sqrt(y*2)/2)
        )

    for idx, i in enumerate(range(0,y,64)):
        dequantized=data[i:i+64]*tab.flatten()
        unzig=zigzag(dequantized)

        _x=(idx*8)%x
        _y=int((idx*8)/x)*8
        result[_y:-y+8, _x:_x+8]=unzig

    udct=scipy.fftpack.idct(scipy.fftpack.idct(result.astype(float), axis=0 , norm='ortho'), axis=1 , norm='ortho')
    udct=np.clip(udct,0,255).astype(np.uint8)
    result= chromaDesubsample(udct,params)
    return result



x = 10
y = 15
img = cv2.imread("zyrafa.jpg")[y:y+128, x:x+12]
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
#plt.imshow(img)
#plt.title('Original')
# plt.show()

Y, Cr, Cb = np.clip(cv2.split(img), 0, 255)
compressed= compress(Y,"4:2:2",[0,0])
#decompressed = decompress(compressed)
# plt.imshow(compressed)
# plt.title('Decompressed')
# plt.show()


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
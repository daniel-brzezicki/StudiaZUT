import scipy.fftpack
import numpy as np
import cv2
import matplotlib.pyplot as plt


def dct2(a):
    return scipy.fftpack.dct( scipy.fftpack.dct( a.astype(float), axis=0, norm='ortho' ), axis=1, norm='ortho' )

def idct2(a):
    return scipy.fftpack.idct( scipy.fftpack.idct( a.astype(float), axis=0 , norm='ortho'), axis=1 , norm='ortho')

def zigzag(A):
    template= n= np.array([
            [0,  1,  5,  6,  14, 15, 27, 28],
            [2,  4,  7,  13, 16, 26, 29, 42],
            [3,  8,  12, 17, 25, 30, 41, 43],
            [9,  11, 18, 24, 31, 40, 44, 53],
            [10, 19, 23, 32, 39, 45, 52, 54],
            [20, 22, 33, 38, 46, 51, 55, 60],
            [21, 34, 37, 47, 50, 56, 59, 61],
            [35, 36, 48, 49, 57, 58, 62, 63],
            ])
    if len(A.shape)==1:
        B=np.zeros((8,8))
        for r in range(0,8):
            for c in range(0,8):
                B[r,c]=A[template[r,c]]
    else:
        B=np.zeros((64,))
        for r in range(0,8):
            for c in range(0,8):
                B[template[r,c]]=A[r,c]
    return B


QY= np.array([
        [16, 11, 10, 16, 24,  40,  51,  61],
        [12, 12, 14, 19, 26,  58,  60,  55],
        [14, 13, 16, 24, 40,  57,  69,  56],
        [14, 17, 22, 29, 51,  87,  80,  62],
        [18, 22, 37, 56, 68,  109, 103, 77],
        [24, 36, 55, 64, 81,  104, 113, 92],
        [49, 64, 78, 87, 103, 121, 120, 101],
        [72, 92, 95, 98, 112, 100, 103, 99],
        ])

QC= np.array([
        [17, 18, 24, 47, 99, 99, 99, 99],
        [18, 21, 26, 66, 99, 99, 99, 99],
        [24, 26, 56, 99, 99, 99, 99, 99],
        [47, 66, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        ])

ones = np.ones((8, 8))


class DATA():
    Y=[]
    Cr=[]
    Cb=[]

def chromaSubsample(data, params, sub=True):
    y,x = data.shape

    result=np.empty((y, int(x/2)))
    if params=="4:2:2" and sub==True:
        for _y in range(0,y):
            for _x in range(0,x,2):
                result[_y][int(_x/2)]=data[_y][_x]
    else:
        return data

    return result

def chromaDesubsample(data, params, sub=True):
    y,x = data.shape

    result=np.empty((y, x*2))
    if params=="4:2:2" and sub==True:
        for _y in range(0,y):
            for _x in range(0,x):
                result[_y][_x*2]=data[_y][_x]
                result[_y][_x*2+1]=data[_y][_x]
    else:
        return data

    return result    



def compress(sourceIm,params,t1,t2,t3):
    Y, Cr, Cb = cv2.split(img)

    data = DATA()
    data.Y = compressHelper(Y,params,t1,False)
    data.Cr = compressHelper(Cr,params,t2)
    data.Cb= compressHelper(Cb,params,t3)

    return data

def compressHelper(data, params, tab, chroma=True):

    cs=chromaSubsample(data,params,chroma)
    cs = cs.astype(int)-128
    cs_y,cs_x = cs.shape
    result=np.zeros(cs_y*cs_x)

    idx=0
    for _y in range(0,cs_y,8):
        for _x in range(0,cs_x,8):
            dct = dct2(cs[_y:_y+8,_x:_x+8])
            #quant=np.round(dct[_y:_y+8,_x:_x+8]//tab).astype(int)
            quant=np.round(dct//tab).astype(int)
            result[idx:idx+64]=zigzag(quant)
            idx+=64
    return result


def initData(params,s, chroma):
    if params == "4:4:4" or not chroma:
        return np.zeros((
            int(np.sqrt(s)),
            int(np.sqrt(s))
        ))
    else:
        return np.zeros((
            int(np.sqrt(s*2)),
            int(np.sqrt(s*2)/2)
        ))

def decompress(data, params,t1,t2,t3):

    Y=decompressHelper(data.Y,params,t1,False)
    Cr=decompressHelper(data.Cr,params,t2)
    Cb=decompressHelper(data.Cb,params,t3)

    return np.dstack([Y,Cr,Cb]).astype(np.uint8)



def decompressHelper(data,params,tab,chroma=True):
    result = initData(params,data.shape[0],chroma)

    y,x=result.shape
    for idx, i in enumerate(range(0,data.shape[0],64)):
        dezigzaged=zigzag(data[i:i+64])
        dequantized=dezigzaged*tab
        _x=(idx*8)%x
        _y=int((idx*8)/x)*8
        result[_y:_y+8, _x:_x+8]=idct2(dequantized)+128

    result= chromaDesubsample(np.clip(result,0,255).astype(np.uint8),params,chroma)
    return result

def createPlots(img,param, t1,t2,t3,name):
    figure, sp = plt.subplots(4, 2)
    figure.set_size_inches(7, 13)
    figure.suptitle(name,fontsize=16)

    #orig
    Y, Cr, Cb = np.clip(cv2.split(img), 0, 255)
    sp[0,0].imshow(img)
    sp[1,0].imshow(Y, cmap=plt.cm.gray)
    sp[2,0].imshow(Cr, cmap=plt.cm.gray)
    sp[3,0].imshow(Cb, cmap=plt.cm.gray)


    #do work
    compressedy= compress(img,param,t1,t2,t3)
    decompressedIm = decompress(compressedy,param,t1,t2,t3)

    #decomp
    decompressedY, decompressedCr, decompressedCb = np.clip(cv2.split(decompressedIm), 0, 255)
    sp[0,1].imshow(decompressedIm)
    sp[1,1].imshow(decompressedY, cmap=plt.cm.gray)
    sp[2,1].imshow(decompressedCr, cmap=plt.cm.gray)
    sp[3,1].imshow(decompressedCb, cmap=plt.cm.gray)

    #dest = "D:/GitHubProjects/StudiaZUT/Systemy multimedialne/Lab8/"
    #plt.savefig(dest+name+'.png')
    plt.show()



images=['zyrafa.jpg']#,'dog.jpg','bugsbunny.jpg']
dims = [(450,300),(300,200),(0,100)]

for dim in dims:
    for image in images:
        x,y = dim
        img = cv2.imread(image)[y:y+128, x:x+128]
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

        createPlots(img,"4:4:4",ones,ones,ones,image[:3]+" "+str(x)+" "+str(y)+" "+" 4-4-4")
        #plt.show()
        createPlots(img,"4:2:2",ones,ones,ones,image[:3]+" "+str(x)+" "+str(y)+" "+" 4-2-2 100pro")
        #plt.show()
        createPlots(img,"4:2:2",QY,QC,QC,image[:3]+" "+str(x)+" "+str(y)+" "+" 4-2-2 50pro")
    # plt.show()
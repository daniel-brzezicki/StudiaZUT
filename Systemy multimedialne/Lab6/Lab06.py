from base64 import decode
from typing import OrderedDict
from cv2 import imread
import numpy as np
import sys
import matplotlib.image as im
import matplotlib.pyplot as plt
import os

def get_size(obj, seen=None):
    """Recursively finds size of objects"""
    size = sys.getsizeof(obj)
    if seen is None:
        seen = set()
    obj_id = id(obj)
    if obj_id in seen:
        return 0
    # Important mark as seen *before* entering recursion to gracefully handle
    # self-referential objects
    seen.add(obj_id)
    if isinstance(obj,np.ndarray):
        size=obj.nbytes
    elif isinstance(obj, dict):
        size += sum([get_size(v, seen) for v in obj.values()])
        size += sum([get_size(k, seen) for k in obj.keys()])
    elif hasattr(obj, '__dict__'):
        size += get_size(obj.__dict__, seen)
    elif hasattr(obj, '__iter__') and not isinstance(obj, (str, bytes, bytearray)):
        size += sum([get_size(i, seen) for i in obj])
    return size


def RLE(data):
    d = data.copy()
    d = d.flatten()

    newData = []

    newData.append(len(data.shape))
    for i in range(len(data.shape)):
        newData.append(data.shape[i])

    counter=0

    current = d[0]
    for i in range(d.shape[0]):
        if(d[i]==current):
            counter+=1
        else:
            newData.append(counter)
            newData.append(current)
            current = d[i]
            counter=1
    
    newData.append(counter)
    newData.append(current)


    return newData


def decodeRLE(data):
    newData=[]
    counters=[]
    values=[]

    shape=[]
    size = data[0]
    data.pop(0)
    for i in range(size):
        shape.append(data[0])
        data.pop(0)

    for i in range(len(data)):
        if(i%2==0):
            counters.append(data[i])
        else:
            values.append(data[i])

    value = 0
    for i in counters:
        for j in range(i):
            newData.append(values[value])
        value+=1


    newData = np.array(newData).reshape(tuple(shape[i] for i in range(len(shape))))
    return newData



class QuadTree:
    def __init__(self, leaf, x, w, y,h):
        self.nodes = []
        self.leaf =0

        self.x = x
        self.width = w
        self.y = y
        self.height = h

    def addNode(self, node):
        self.nodes.append(node)

    def setLeaf(self, leaf):
        self.leaf = leaf

    def getNodesCount(self):
        return len(self.nodes)



def check(source, shape, value):
    for i in range(source.shape[shape]):
        if shape==0:
            if not np.all(source[i]==value):
                return False
        elif shape==1:
            if not np.all(source[:,i]==value):
                return False
    return True


def quadOper(source, x, w, y, h):
    tree = QuadTree(0,x, w, y, h)
    src = source[x:w, y:h]

    leafPos = check(src,0,src[0])
    if(leafPos):
        leafPos= check(src,1,src[:,0])

    if leafPos:
        tree.setLeaf(source[x,y])
    else:
        if (h - y) == 1:
            tree.addNode(quadOper(source, x, (w + x) // 2, y, h))
            tree.addNode(quadOper(source, ((w + x) // 2), w, y, h))
        elif (w - x) == 1:
            tree.addNode(quadOper(source, x, w, y, (y + h) // 2 ))
            tree.addNode(quadOper(source, x, w, ((y + h) // 2 ), h)) 
        else:
            tree.addNode(quadOper(source, x, (w + x) // 2, y, (y + h) // 2 )) 
            tree.addNode(quadOper(source, ((w + x) // 2), w, ((y + h) // 2 ), h)) 
            tree.addNode(quadOper(source, ((w + x) // 2), w, y, (y + h) // 2 )) 
            tree.addNode(quadOper(source, x, (w + x) // 2, ((y + h) // 2 ), h))
            
    return tree

def quadEncode(source):
    return quadOper(source, 0, source.shape[0], 0, source.shape[1])

def decode(tree,decoded):
    nCount = tree.getNodesCount()
    if nCount > 0:
        for i in range(nCount):
            decoded = decode(tree.nodes[i], decoded)
    else:
        decoded[tree.x:tree.width, tree.y:tree.height] = tree.leaf
    return decoded

def quadDecode(tree):
    result = np.zeros((tree.width, tree.height, 3)).astype(int)
    result = decode(tree, result)

    return result



def ShowResults(originalData, compressedData, decompressedData, title):
    originalSize= get_size(originalData)
    compressedSize = get_size(compressedData)
    decompressedSize = get_size(decompressedData)

    compare = originalData==decompressedData

    print(title)
    print("Wielkosc zdekompresowana: ",decompressedSize)
    print("Stopien kompresji: ", originalSize/compressedSize)
    print("Wielkosc w procentach: ",100*compressedSize/originalSize," %")
    print("Czy dane sa identyczne jak oryginal?: ", compare.all())
    plt.imshow(decompressedData)
    plt.show()


#a=np.array([1,1,1,1,1,2,2,2,3,4,5,6,6,6,6,1])
images = os.listdir("D:/GitHubProjects/StudiaZUT/Systemy multimedialne/Lab6/")[2:]
for image in images:
    img = im.imread(image)
    rleEnc = RLE(img)
    rleDec = decodeRLE(rleEnc)
    ShowResults(img,rleEnc,rleDec,"======= RLE:")

    quadEnc= quadEncode(img)
    quadDec = quadDecode(quadEnc)
    ShowResults(img,quadEnc,quadDec,"======= Drzewo czworkowe:")





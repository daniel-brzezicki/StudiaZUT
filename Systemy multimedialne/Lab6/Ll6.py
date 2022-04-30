from base64 import decode
from typing import OrderedDict
import numpy as np
import sys

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
        pass
    elif isinstance(obj, dict):
        size += sum([get_size(v, seen) for v in obj.values()])
        size += sum([get_size(k, seen) for k in obj.keys()])
    elif hasattr(obj, '__dict__'):
        size += get_size(obj.__dict__, seen)
    elif hasattr(obj, '__iter__') and not isinstance(obj, (str, bytes, bytearray)):
        size += sum([get_size(i, seen) for i in obj])
    return size



# step=0
# for i in tqdm(range(0,11100000)):
#     step=step+0.0000001

def RLE(data):
    d = data.copy()
    d = d.flatten()

    newData = []#np.empty(d.shape[0]).astype(data.dtype)

    counter=0
    newDataPlace=0

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


def decodeRLE(data,shape):
    newData=[]
    counters=[]
    values=[]

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

    newData = np.array(newData).reshape(shape)
    return newData





a=np.array([1,1,1,1,1,2,2,2,3,4,5,6,6,6,6,1])
#a=np.arange(0,521,1)
shape = a.shape
print(shape)
print(a)
out = RLE(a)
print(out)

nout = decodeRLE(out,shape)
print(nout)




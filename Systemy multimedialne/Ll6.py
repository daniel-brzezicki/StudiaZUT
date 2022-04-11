from typing import OrderedDict
import numpy as np
import sys
from tqdm import tqdm

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

    newData = np.empty(d.shape[0]).astype(data.dtype)

    counter=1
    newDataPlace=0
    for i in range(d.shape[0]):
        #print(i,d[i])
        
        if(i+1<d.shape[0]):
            if(d[i]==d[i+1]):
                counter=counter+1
            else:
                newData[newDataPlace]=counter
                newData[newDataPlace+1]=d[i]
                newDataPlace=newDataPlace+2
                counter=1
        else:
                newData[newDataPlace]=counter
                newData[newDataPlace+1]=d[i]
                newDataPlace=newDataPlace+2
                counter=1

        

    return newData
    #for i in range(d)


a=np.array([1,1,1,1,1,2,2,2,3,4,5,6,6,6,6,1])
out = RLE(a)
print(out)



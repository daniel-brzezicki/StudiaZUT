import math as m
import numpy as np
import scipy as sc
import pandas as pd
import scipy.sparse as spr
from sklearn.datasets import fetch_rcv1

print("Zadanie 1")
def freq(x, prob=True):
    xi=np.unique(x)
    pi={}
    for i in x:
        if i in pi:
            pi[i]+=1
        else:
            pi[i]=1
    if prob:
        for i in pi:
            pi[i]=pi[i]/len(x)
    return xi, pi

file=pd.read_csv('zoo.csv')
xi=[]
xi,pi=freq(file['eggs'])
print(freq(file['eggs']))

print("Zadanie 2")
def freq2(x,y, prob=True):
    xi=np.unique(x)
    yi=np.unique(y)
    pi={}
    
    for i in range(len(x)):
        if (x[i],y[i]) in pi:
            pi[x[i],y[i]]+=1
        else:
            pi[x[i],y[i]]=1
    if prob:
        for i in pi:
            pi[i]=pi[i]/len(x)
    return xi, yi, pi
yi=[]
xi,yi,pi=freq2(file['eggs'],file['milk'])
print(freq2(file['eggs'],file['milk']))

print("Zadanie 3")
def entropy(x):
    xi,pi=freq(x)
    h=0
    for i in pi:
        h+=pi[i]*m.log2(pi[i])
    return -h

def entropy_xy(x,y):
    xi,yi,pi=freq2(x,y)
    h=0
    for i in pi:
        h+=pi[i]*m.log2(pi[i])
    return -h

def infogain(x,y):
    h_y=entropy(y)
    h_x=entropy(x)
    h_xy=entropy_xy(x,y)
    i=h_x+h_y-h_xy
    return i

i=infogain(file['type'],file['eggs'])
print(i)

print("Zadanie 4")
zoo_infogain={}
for col2 in file.columns:
    if col2 != 'type':
        zoo_infogain['type',col2] = infogain(file['type'],file[col2])
zoo_infogain=sorted(zoo_infogain.items(), key=lambda item: item[1])
print(zoo_infogain)

print("Zadanie 5")

def freq_spar(x, prob=True):
    x_len = x.shape[0]
    row, col = x.nonzero()
    elem_nonzero = len(row)
    xi=[]
    pi={}
    if row.size>0:
        for i in row:
            if x[i,0] in pi:
                pi[x[i,0]]+=1
            else:
                pi[x[i,0]]=1
                xi.append(x[i,0])
    if x_len != elem_nonzero: xi.append(0)
    pi[0]=x_len-elem_nonzero
    if prob:
        for i in pi:
            pi[i]=pi[i]/x_len
    return xi, pi

def freq2_spar(x,y, prob=True):
    x_len = x.shape[0]
    x_row, x_col = x.nonzero()
    y_row, y_col = y.nonzero()
    x_elem_nonzero = len(x_row)
    y_elem_nonzero = len(y_row)
    pi={}
    xi = []
    yi = []
    if x_row.size>0:
        for i in x_row:
            xi.append(x[i,0])
            if i in y_row:
                if (x[i,0],y[i,0]) in pi:
                    pi[x[i,0],y[i,0]]+=1
                else:
                    pi[x[i,0],y[i,0]]=1
            else:
                if (x[i,0],0) in pi:
                    pi[x[i,0],0]+=1
                else:
                    pi[x[i,0],0]=1
    if y_row.size>0:
        for i in y_row:
            yi.append(y[i,0])
            if i not in x_row:
                if (0,y[i,0]) in pi:
                    pi[0,y[i,0]]+=1
                else:
                    pi[0,y[i,0]]=1
    yi.append(0)
    xi.append(0)
    xi=np.unique(xi)
    yi=np.unique(yi)
    suma=sum(pi.values())
    pi[0,0]=x_len-suma
    if prob:
        for i in pi:
            pi[i]=pi[i]/x_len
    return xi, yi, pi



print("Zadanie 6")
def entropy_spar(x):
    xi,pi=freq_spar(x)
    h=0
    for i in pi:
        h+=pi[i]*m.log2(pi[i])
    return -h

def entropy_xy_spar(x,y):
    xi,yi,pi=freq2_spar(x,y)
    h=0
    for i in pi:
        h+=pi[i]*m.log2(pi[i])
    return -h

def infogain_spar(x,y):
    h_y=entropy_spar(y)
    h_x=entropy_spar(x)
    h_xy=entropy_xy_spar(x,y)
    i=h_x+h_y-h_xy
    return i

rcv1=fetch_rcv1()
x=rcv1.data
y=rcv1.target[:,87]
info=[]
print(info)
for i in range(x.shape[1]):
    info.append((infogain_spar(x.getcol(i), y), i))
info=info.sort()
print(info[0:49])
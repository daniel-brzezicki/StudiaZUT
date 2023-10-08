import pandas as ps
import numpy as np
import scipy.stats
import matplotlib.pyplot as plt
import math
from PIL import Image
import scipy.sparse as spr
from sklearn import datasets
from sklearn.decomposition import PCA


def distp(X, C):
    de = np.zeros([len(X), len(C)])

    for i, xi in enumerate(X):
        for k, ck in enumerate(C):
            de[i, k] = np.sqrt((xi - ck) @ np.transpose(xi - ck))

    return de


def distm(X,C,V):
    dm=[]
    for i, xi in enumerate(X):
        vector = []
        for k, ck in enumerate(C):
            vector.append(np.sqrt(np.dot(np.dot((xi-ck),np.cov(xi)),(xi-ck).T)))
        dm.append(vector)
    return dm


def ksrodki(x,k, e= True):
    rnd = x[np.random.randint(x.shape[0], size=k)]

    n = np.ones((len(x),1))
    nOld = -np.ones((len(x),1))

    count=0
    maxC=100
    while 1:
        count+=1
        if e:
            distances = distp(x,rnd)
            n = np.argmin(distances,axis=1)
        else:
            distances = distm(x,rnd, np.cov(x))
            n = np.argmin(distances,axis=1)
        C=[]
        sumG=0
        all=0
        for g in range(k):
            v= []
            for c in range(x.shape[1]):
                sumG=0
                all =0
                for i in range(len(x)):
                    if n[i]==g:
                        sumG+=x[i,c]
                        all+=1
                if all!=0:
                    v.append(sumG/all)
                else:
                    v.append(0)
            C.append(v)
        C=np.array(C)

        flag=False
        for i in range(len(x)):
            if count>=maxC:
                flag=False
                break
            if n[i]!= nOld[i]:
                nOld=n
                flag=True
                break
        if flag == True:
            continue
        break
    return C, n

def F(C,CX):
    return 


plt.figure()
x=np.dot(np.random.randn(400,2),np.random.rand(2,2))

C, CX = ksrodki(x,3,True)
plt.scatter(x[:,0],x[:,1], c=CX,zorder=0)
plt.scatter(C[:,0],C[:,1], c='red',zorder=1,marker='o')

plt.figure()
C,CX = ksrodki(x,3,False)
plt.scatter(x[:,0],x[:,1], c=CX,zorder=0)
plt.scatter(C[:,0],C[:,1], c='red',zorder=1,marker='o')

plt.show()


data = ps.read_csv(r"c:\Users\danie\source\repos\PIADLab8\autos.csv")
data = data[["width", "height"]]
X = np.array(data)
X = X.astype(float)


k = 3
C, CX = ksrodki(X, k, True)

plt.scatter(X[:,0],X[:,1], c=CX,zorder=0)
plt.scatter(C[:,0],C[:,1], c='red',zorder=1,marker='o')
plt.show()


C, CX = ksrodki(X, k, False)
plt.scatter(X[:,0],X[:,1], c=CX,zorder=0)
plt.scatter(C[:,0],C[:,1], c='red',zorder=1,marker='o')
plt.show()




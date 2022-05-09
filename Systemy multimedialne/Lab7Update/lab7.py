import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf
import sounddevice as sd
import os


def quantize(sourceSd, bits): 
    m=0
    n=0
    typ = sourceSd.dtype
    d = 2**bits-1
    
    sound = sourceSd.astype(np.float32)

    if np.issubdtype(typ, np.floating):
        m=-1
        n=1
    else:
        m=np.iinfo(typ).min
        n=np.iinfo(typ).max
    
    sound = (sound -m) / (n-m)
    sound = np.round(sound*d)/d
    sound = ((sound*(n-m))+m).astype(typ)

    return sound

A=87.6

def AlawEncode(x,bits):
    result=x.copy()
    idx1 = np.abs(x) < (1/A)
    idx2 = np.abs(x) >= (1/A)

    result[idx1]=np.sign(x[idx1])*((A*np.abs(x[idx1]))/(1+np.log(A)))
    result[idx2]=np.sign(x[idx2])*((1+np.log(A*np.abs(x[idx2])))/(1+np.log(A)))

    for i in range(len(result)):
        result[i]=quantize(result[i],bits)
    return result


def AlawDecode(y):
    result=y.copy()#np.zeros(y.shape)
    idy1= np.abs(y) < (1/(1+np.log(A)))
    idy2=np.abs(y) >= (1/(1+np.log(A)))

    result[idy1]=np.sign(y[idy1]) * ((np.abs(y[idy1]) * (1+np.log(A))))/A
    result[idy2]=np.sign(y[idy2]) * ((np.exp(np.abs(y[idy2])*(1+np.log(A)))-1))/A

    return result

def DPCMencode(source, bits):
    e=source[0]
    result=source.copy()
    for i in range(1,len(source)):
        y=quantize(result[i]-e,bits)
        e+=y
        result[i]=y

    return result

def DPCMdecode(source):
    result=source.copy()
    for i in range(1,len(source)):
        result[i]=result[i-1]+result[i]
    return result
    
def plot(sourceSd, dpcm,alaw,Fs, ms, file):
    t=ms
    m=int(Fs*(t/1000))

    np.arange(0,m)/Fs
    plt.figure()
    plt.subplot(3,1,1)
    plt.title(file+ ' Original')

    plt.plot(np.arange(0,m)/Fs,sourceSd[0:m])

    plt.subplot(3,1,2)
    plt.title(file+ ' Alaw decoding')
    plt.plot(np.arange(0,m)/Fs,alaw[0:m])

    plt.subplot(3,1,3)
    plt.title(file+ ' DPCM decoding')
    plt.plot(np.arange(0,m)/Fs,dpcm[0:m])
    
    dest="C:/Users/student/Desktop/Lab7/"
    #plt.savefig(dest+file+'.png')
    plt.show()


sounds = os.listdir("C:/Users/student/Desktop/Lab7/")[1:]

bits=[8,6,4,2]

for file in sounds:
    sound, freq=sf.read(file, dtype=np.float32)
    
    for bit in bits:
        alawEncode = AlawEncode(sound, bit)
        alawDecode = AlawDecode(alawEncode)
        dpcmEncode = DPCMencode(sound, bit)
        dpcmDecode = DPCMdecode(dpcmEncode)
        plot(sound,dpcmDecode,alawDecode,freq,2000, file+str(bit))

print('done')
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
    idx2 =  np.abs(x) >= (1/A) #np.logical_not(idx1)

    result[idx1]=np.sign(x[idx1])*((A*np.abs(x[idx1]))/(1+np.log(A)))
    result[idx2]=np.sign(x[idx2])*((1+np.log(A*np.abs(x[idx2])))/(1+np.log(A)))

    for i in range(len(result)):
        result[i]=quantize(result[i],bits)
    return result


def AlawDecode(y):
    result=y.copy()#np.zeros(y.shape)
    idy1= np.abs(y) < (1/(1+np.log(A)))
    idy2=np.abs(y) >= (1/(1+np.log(A)))#np.logical_not(idy1)

    result[idy1]=np.sign(y[idy1]) * ((np.abs(y[idy1]) * (1+np.log(A))))/A
    result[idy2]=np.sign(y[idy2]) * ((np.exp(np.abs(y[idy2])*(1+np.log(A)))-1))/A

    #result=quantize(result,bits)
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
    
def plot(sourceSd, dpcm,alaw, file):
    x=np.linspace(-1,1,1000)

    plt.figure()
    plt.subplot(3,1,1)
    plt.title(file+ ' Original')

    plt.plot(x,sourceSd[0:1000])

    plt.subplot(3,1,2)
    plt.title(file+ ' Alaw decoding')
    plt.plot(x,alaw[0:1000])

    plt.subplot(3,1,3)
    plt.title(file+ ' DPCM decoding')
    plt.plot(x,dpcm[0:1000])
    #spectrum(sourceSd,Fs)\
    
    dest='C:/Users/HP/Documents/GitHub/StudiaZUT/Systemy multimedialne/Lab7/'
    plt.savefig(dest+file+'.png')
    plt.show()

sounds = os.listdir("C:/Users/HP/Documents/GitHub/StudiaZUT/Systemy multimedialne/Lab7/")[1:]



#sound, freq = sf.read(sounds[0], dtype=np.int32)


#Testy
#x=np.linspace(-1,1,1000)
#sound=0.9*np.sin(np.pi*x*4)
bits=[8,6,4,2]

for file in sounds:
    sound, freq=sf.read(file, dtype=np.float32)
    #x=np.linspace(-1,1,1000)
    #sound=0.9*np.sin(np.pi*x*4)
    
    for bit in bits:
        alawEncode = AlawEncode(sound,bit)
        #quant=quantize(alawEncode,bit)
        #for i in range(len(alawEncode)):
            #alawEncode[i] = quantize(alawEncode[i],bit)
        alawDecode=AlawDecode(alawEncode)
        dpcmEncode = DPCMencode(sound,bit)
        dpcmDecode = DPCMdecode(dpcmEncode)
        #sd.play(alawDecode, samplerate=freq, blocking=True)
        plot(sound,dpcmDecode,alawDecode, file+str(bit))

print('done')
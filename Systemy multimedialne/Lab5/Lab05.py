from tracemalloc import start
from matplotlib.pyplot import axis
import matplotlib.pyplot as plt
import numpy as np
import random
import matplotlib.pyplot as plt
import soundfile as sf
from scipy.interpolate import interp1d



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

def decimate(sourceSd, n):
    return sourceSd[::n]

def interpolate(sourceSd,fs,typ):
    t = sourceSd[0]/fs
    print(t)
    


    return

sound, freq = sf.read('sing_low1.wav')

a = np.round(np.linspace(0,255,255,dtype=np.uint8))

s = quantize(a, 8)
#plt.plot(s[:250])
#plt.show()

#print(sound.shape)
dec = decimate(sound,10)
#print(dec.shape)

interpolate(sound,48000,'linear')

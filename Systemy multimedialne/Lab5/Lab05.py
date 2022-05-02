from tracemalloc import start
from matplotlib.pyplot import axis
import matplotlib.pyplot as plt
import numpy as np
import random
import matplotlib.pyplot as plt
import soundfile as sf
import sounddevice as sd
from scipy.interpolate import interp1d
import scipy.fftpack as scp
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

def decimate(sourceSd, n):
    return sourceSd[::n]

def interpolate(sourceSd,Fs,nFs,typ="linear"):
    t = len(sourceSd[:])/Fs

    x= np.arange(0,t,1/Fs)
    x1=np.arange(0,t,1/nFs)

    # print(t)
    # print(x)
    # print(x1)

    i = interp1d(x,sourceSd,typ,fill_value="extrapolate")
    return i(x1).astype(sourceSd.dtype)


def plot(sourceSd, Fs, ms,title,dest):
    t=ms
    m=int(Fs*(t/1000))

    plt.figure()
    plt.subplot(2,1,1)
    plt.title(title)

    plt.plot(np.arange(0,m)/Fs,sourceSd[0:m])

    plt.subplot(2,1,2)
    spectrum(sourceSd,Fs)

    plt.savefig(dest+'/'+title+'.png')

    #plt.show()

def spectrum(sourceSd,Fs):
    fsize = 2 ** 8
    yf = scp.fft(sourceSd, fsize)
    plt.plot(np.arange(0, Fs / 2, Fs / fsize), 20 * np.log10(np.abs(yf[:fsize // 2])))



def plotWithFreq(sourceSd,Fs, nFs,ms,title ,dest):
    t=ms

    plt.figure()

    plt.subplot(3,1,1)
    plt.title(title+' decymacja')
    size = 2 ** 8
    yf = scp.fft(sourceSd, size)
    d = spectrum(decimate(sourceSd,int(Fs/nFs)),nFs)
    plt.subplot(3,1,2)
    plt.title('inter. linear')
    iLin = spectrum(interpolate(sourceSd,Fs,nFs,"linear"),nFs)
    plt.subplot(3,1,3)
    plt.title('inter. cubic')
    iKw = spectrum(interpolate(sourceSd,Fs,nFs,"cubic"),nFs)
    
    plt.savefig(dest+'/'+title+'.png')
    #plt.show()

sounds = os.listdir("D:/GitHubProjects/StudiaZUT/Systemy multimedialne/Lab5/")[1:]
sing = sounds[:6]
sin = sounds[6:]

freqs = [2000,4000,8000,16000,24000,41000,16950]

# for s in sing:
#     print(s)

# for s in sin:
#     sound, freq = sf.read(s)
#     plot(quantize(sound, 4),freq,100,s +' 4 bit','Quantize')
#     plot(quantize(sound, 8),freq,100,s+' 8 bit','Quantize')
#     plot(quantize(sound, 16),freq,100,s+' 16 bit','Quantize')
#     plot(quantize(sound, 24),freq,100,s+' 24 bit','Quantize')

#     for f in freqs:
#         plotWithFreq(sound , freq, f, 100, s+' '+str(freq)+' to '+str(f),'ChangeFreq')


#     print(s)


#sound, freq = sf.read('sing_low1.wav')

#a = np.round(np.linspace(0,255,255,dtype=np.uint8))

#plt.plot(s[:250])
#plt.show()

#print(sound.shape)
#dec = decimate(sound,10)
#print(dec.shape)

#interpolate(sound,48000,16000,'linear')

# SIN60Hz
#
#  Kwantyzacja dla 4 bitów dźwięk ma inne brzmienie niż oryginał, przy 8 bitach pojawia się szum, 
#   natomiast przy 16 jak i 24 bitach nie słychać żadnej różnicy między oryginałem
#  Decymacja dla częstotliwości 2000,4000, 8000, 16000, 24000 brzmią tak jak oryginał, zmiany brzmieniowe pojawiają się zaś
#   przy 16950 oraz 41000
#  Przy interpolacji liniowej oraz kwadratowej dźwięki brzmią tak samo jak oryginał


# SIN440Hz
#
#  Kwantyzacja podobnie jak przykład wyżej, dla 4 bitów, dźwięk znacznie się różni od oryginału. Przy 8, 16 oraz 24
#   nie występuje żadna znacząca różnica między oryginałem.
#  Decymacja identycznie jak przykład wyżej. 2000, 4000, 8000, 16000, 24000 brzmią jak oryginał, zaś 16950, 41000 
#   słyszalne są zmiany
#  Przy interpolacji liniowej oraz kwadratowej dźwięki brzmią tak samo jak oryginał


# singMedium1
#
#  Kwantyzacja dla 4 bitów dźwięk zniekształcony, dla 8 bitów występuje szum, natomiast dla 16 jak i 24 dźwięk jest
#   praktycznie taki sam jak ogryginalny.
#  Decymacja 2000, 4000, 8000, 16000, 16950, 41000 dźwięki zbliżone do oryginału. Przy 24000Hz dźwięki są niższe niż 
#   w oryginale.
#  Przy interpolacji liniowej jak i kwadratowej dźwięki różnią się jedynie przy 24000Hz.


# singLow1
# 
#  Kwantyzacja tak samo jak w singMedium1
#  Decymacja przy 2000, 4000, 8000, 16000 oraz 24000Hz słyszalna jest różnica między oryginałem, wyższe czestotliowści
#   bez różnicy
#  Interpolacja liniowa, jak i kwadratowa dla częstotliwości poniżej 24000Hz z słyszalnymi różnicami, wartości 
#   powyżej, bez znaczących różnic



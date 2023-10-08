import math as m
import matplotlib.pyplot as plt
import numpy as np
from scipy.fft import fft as fft

#utility function
def binconv(str, limit = None):
    output=[]
    res = ''.join(format(ord(i), '07b') for i in str)
    for i in range(len(res)):
        if res[i]=="0":
            output.append(0)
        elif res[i]=="1":
            output.append(1)
    if limit != None:
        return output[0:limit]
    return output

sent="abc"

#variables
letter_time = 1
bits_in_letter = 7
fs = 7000

ts = 1/fs

N = m.ceil(len(sent) * letter_time / ts)

A=2 #zmienna do demodulacji

A1=1
A2=2
W=6
#W=len(sent) * letter_time * bits_in_letter
fn=W*bits_in_letter
fn1=(W+1)*bits_in_letter
fn2=(W+2)*bits_in_letter

def stretch(binary):
    t = []
    output = []
    for i in range(N):
        t.append(i * ts)
        if binary[m.floor(t[i]*7)] == 0:
            output.append(0)
        else:
            output.append(1)
    return t, output

#functions
def ask_function(binary):
    Tc=1
    B = len(sent)
    Tb = Tc/B
    
    t = []
    output = []
    x_t=[]
    p_t=[]
    c_t=[]
    sum=0
    h=2000
    czas_aktualnego_bitu = 0

    for i in range(N):
        t.append(i * ts)
        if binary[m.floor(t[i]*7)] == 0:
            output.append(A1*m.sin(2*m.pi*fn*t[i]))
        else:
            output.append(A2*m.sin(2*m.pi*fn*t[i]))

    for i in range(N):
        x_t.append(A*m.sin(2*m.pi*fn*t[i])*output[i])

        if czas_aktualnego_bitu > Tb:
            czas_aktualnego_bitu = 0
            sum = 0

        sum+=x_t[i]
        p_t.append(sum)
        czas_aktualnego_bitu += 1/fs
        
        c_t.append(1 if p_t[i]>h else 0)  


    return t, output, x_t, p_t, c_t
    
def psk_function(binary):
    t = []
    output = []
    x_t=[]
    p_t=[]
    c_t=[]
    sum=0
    h=490
    for i in range(N):
        t.append(i * ts)
        if binary[m.floor(t[i]*7)] == 0:
            output.append(m.sin(2*m.pi*fn*t[i]))
        else:
            output.append(m.sin(2*m.pi*fn*t[i]+m.pi))

    for i in range(N):
        x_t.append(A*m.sin(2*m.pi*fn*t[i])*output[i])

        sum+=x_t[i]
        p_t.append(sum)

        c_t.append(1 if p_t[i]>h else 0)  

    return t, output, x_t, p_t, c_t

def fsk_function(binary):
    t = []
    output = []
    x1_t=[]
    x2_t=[]
    p_t=[]
    p1_t=[]
    p2_t=[]
    sum1=0
    sum2=0
    c_t=[]
    for i in range(N):
        t.append(i * ts)
        if binary[m.floor(t[i]*7)] == 0:
            output.append(m.sin(2*m.pi*fn1*t[i]))
        else:
            output.append(m.sin(2*m.pi*fn2*t[i]))

    for i in range(N):
        #if binary[m.floor(t[i]*7)] == 0:
        x1_t.append(A*m.sin(2*m.pi*fn1*t[i])*output[i])
            
            #p_t.append(sum1)
        #else:
        x2_t.append(A*m.sin(2*m.pi*fn2*t[i])*output[i])
            
            #p_t.append(sum2)

        sum1+=x1_t[i]
        sum2+=x2_t[i]
        p1_t.append(sum1)
        p2_t.append(sum2)

        p_t.append(-p1_t[i]+p2_t[i])

        c_t.append(1 if p_t[i]>0 else 0) 

    return t, output, x1_t, x2_t, p_t, c_t

binary = binconv(sent)
print(binary)
t, s = stretch(binary)

t_ask, s_ask, x_ask, p_ask, c_ask = ask_function(binary)
t_psk, s_psk, x_psk, p_psk, c_psk = psk_function(binary)
t_fsk, s_fsk, x1_fsk, x2_fsk, p_fsk, c_fsk = fsk_function(binary)

fig, ax = plt.subplots(4, 1, figsize=(12, 9), sharex=True)

ax[0].plot(t, s)
ax[0].set_title('binary')
ax[0].grid()

ax[1].plot(t_ask,s_ask)
ax[1].set_title('ask')
ax[1].grid()

ax[2].plot(t_psk,s_psk)
ax[2].set_title('psk')
ax[2].grid()

ax[3].plot(t_fsk,s_fsk)
ax[3].set_title('fsk')
ax[3].grid()

plt.savefig("Ask-psk-fsk.png")
plt.show()

fig, ax = plt.subplots(4, 1, figsize=(12, 9), sharex=True)

ax[0].plot(t_ask, x_ask)
ax[0].set_title('x_t ask')
ax[0].grid()

ax[1].plot(t_psk,x_psk)
ax[1].set_title('x_t psk')
ax[1].grid()

ax[2].plot(t_fsk,x1_fsk)
ax[2].set_title('x1_t fsk')
ax[2].grid()

ax[3].plot(t_fsk,x2_fsk)
ax[3].set_title('x2_t fsk')
ax[3].grid()

plt.savefig("x.png")
plt.show()

fig, ax = plt.subplots(3, 1, figsize=(12, 9), sharex=True)

ax[0].plot(t_ask, p_ask)
ax[0].set_title('p_t ask')
ax[0].grid()

ax[1].plot(t_psk,p_psk)
ax[1].set_title('p_t psk')
ax[1].grid()

ax[2].plot(t_psk,p_fsk)
ax[2].set_title('p_t fsk')
ax[2].grid()

plt.savefig("p.png")
plt.show()

fig, ax = plt.subplots(4, 1, figsize=(12, 9), sharex=True)

ax[0].plot(t, s)
ax[0].set_title('binary')
ax[0].grid()

ax[1].plot(t_ask, c_ask)
ax[1].set_title('c_t ask')
ax[1].grid()

ax[2].plot(t_psk,c_psk)
ax[2].set_title('c_t psk')
ax[2].grid()

ax[3].plot(t_fsk,c_fsk)
ax[3].set_title('c_t fsk')
ax[3].grid()

plt.savefig("c.png")
plt.show()
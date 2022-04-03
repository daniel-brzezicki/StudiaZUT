from tkinter import Frame
import cv2
import pyaudio
import numpy as np
import time
import matplotlib.pyplot as plt
import soundfile as sf


#ZADANIE 1 - DOGRAC W DOMU Z KAMERY
def zad1():
    cap = cv2.VideoCapture(0)#cv2.VideoCapture("D:/Pliki/repos/SystemyMultimedialne/Lab2/clip_1.mp4") #przechwytywanie z pliku

    fourcc = cv2.VideoWriter_fourcc(*'mp4v')

    height=300
    width=200
    dim=(width,height)

    out = cv2.VideoWriter('changed_clip.mp4', fourcc, 20.0, dim)
    original =cv2.VideoWriter('original_clip.mp4', fourcc, 20.0, (640,480))

    if not cap.isOpened():
        print("Cannot open camera")
        exit()
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Can't receive frame (stream end?). Exiting ...")
            break
        
        flipped = cv2.flip(frame, 1)

        cv2.imshow('frame', flipped)

        y=50
        x=50
        crop_img = flipped[y:(y+height), x:(x+width)]

        out.write(crop_img)
        original.write(frame)


        if cv2.waitKey(1) == ord('q'):
            break


    cap.release()
    cv2.destroyAllWindows()

    out.release()
    original.release()


#ZADANIE 2
def process_data(in_data, frame_count, time_info, flag):
    global Frame_buffer, frame_idx, delay_idx
    in_audio_data = np.frombuffer(in_data, dtype=np.int16)

    ch = in_audio_data.copy()
    ch[:] = 0

    Frame_buffer[frame_idx:(frame_idx+CHUNK),0]=in_audio_data

    #print("fra ",np.int16(Frame_buffer[frame_idx:(frame_idx+CHUNK),0]))
    #print(in_audio_data)
    ################################
    ## Do something wih data
    if(frame_idx<delay):
        out_audio_data = ch
    else:
        proper_audio = np.int16(Frame_buffer[delay_idx:(delay_idx+CHUNK),0])
        #print(proper_audio)
        out_audio_data=proper_audio
        delay_idx+=CHUNK

    ################################
    Frame_buffer[delay_idx:(delay_idx+CHUNK),1]=out_audio_data
    out_data =  out_audio_data.tobytes()
    frame_idx+=CHUNK
    return out_data, pyaudio.paContinue


def zad2():
    ##ustawienia do przechwytywania
    stream = audio.open(input_device_index =1,
                        output_device_index=3,
                        format=FORMAT,
                        channels=CHANNELS,
                        rate=FS,
                        input=True,
                        output=True,
                        frames_per_buffer=CHUNK,
                        stream_callback=process_data
                        )

    global Frame_buffer,frame_idx, delay_idx,delay

    delay_idx=0
    N=10
    buffer= np.zeros(((N+1)*FS,2))
    Frame_buffer = np.zeros(((N+1)*FS,2))
    frame_idx=0
    delay=1

    silent_buffer=np.zeros((int((delay+1)*FS),2))
    stream.start_stream()
    while stream.is_active():
        time.sleep(N)
        stream.stop_stream()
    stream.close()

    print(silent_buffer.shape)
    print(Frame_buffer.shape)

    
    x=[]
    x.extend(silent_buffer[:,0].tolist())
    x.extend(Frame_buffer[:,0].tolist())
    plt.subplot(2,1,1)
    plt.plot(x)
    plt.subplot(2,1,2)
    plt.plot(Frame_buffer[:,0])
    plt.show()




audio = pyaudio.PyAudio()

FORMAT = pyaudio.paInt16 
CHANNELS = 1
FS = 44100
CHUNK = 1024

#1 - sluchawki mikro
#2 - slucahwy
zad2()
#zad1()





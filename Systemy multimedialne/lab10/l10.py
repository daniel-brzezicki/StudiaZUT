import numpy as np
import os
import cv2
import matplotlib.pyplot  as plt
import matplotlib.image  as im


#kompresja jpeg
# img=cv2.imread('0000.png')
# encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 50]
# result, encimg = cv2.imencode('.jpg', img, encode_param)
# decimg = cv2.imdecode(encimg, 1)

# fig, axs = plt.subplots(1, 2 , sharey=True   )
# axs[0].imshow(img)
# axs[1].imshow(decimg)

# cv2.imwrite('0000_1.png',decimg)



# #rozmazywanie obrazu
# blur = cv2.blur(img,(5,5))
# blur = cv2.GaussianBlur(img,(5,5),0)
# median = cv2.medianBlur(img,5)
# blur = cv2.bilateralFilter(img,5,75,75)

def MSE(K,I):
    height, length, d = K.shape
    print(K.shape)
    


    pass


images = os.listdir("C:/Users/student/Desktop/lab10")[1:]

for file in images:
    img = im.imread(file)

    MSE(img,img)
    plt.imshow(img)
    plt.show()
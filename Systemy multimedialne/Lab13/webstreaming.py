from sklearn.utils import resample
from imutils.video import VideoStream
from flask import Response
from flask import Flask
from flask import render_template
from flask import request
import threading
import argparse
import datetime
import imutils
import time
import cv2
import numpy as np


time.sleep(2.0)
outputFrame = None
lock = threading.Lock()
app = Flask(__name__,template_folder='templates')
vs = VideoStream(0).start()#VideoStream(src=0).start()

showIconInCorner=False
showDateTime=False
pixelEffect=False
sepiaEffect=False
sharpenEffect=False
pencilEffect=False

effects = [showIconInCorner,showDateTime,pixelEffect,sepiaEffect,sharpenEffect,pencilEffect]

def clearEffects():
	global showIconInCorner,showDateTime,pixelEffect,sepiaEffect,sharpenEffect,pencilEffect
	showIconInCorner=False
	showDateTime=False
	pixelEffect=False
	sepiaEffect=False
	sharpenEffect=False
	pencilEffect=False

def changeValue(flag):
	if flag:
		flag=False
	else:
		flag=True
	return flag


@app.route("/", methods=['GET','POST'])
def index():
	global vs,showIconInCorner,showDateTime,pixelEffect,sepiaEffect,sharpenEffect,pencilEffect

	if(request.method=='GET'):
		return render_template("index.html")
	elif(request.method=='POST'):
		if(request.form.get('showIconInCorner')):
			showIconInCorner=changeValue(showIconInCorner)
		if(request.form.get('showDateTime')):
			showDateTime=changeValue(showDateTime)
		if(request.form.get('pixelEffect')):
			pixelEffect=changeValue(pixelEffect)
		if(request.form.get('sepiaEffect')):
			sepiaEffect=changeValue(sepiaEffect)
		if(request.form.get('sharpenEffect')):
			sharpenEffect= changeValue(sharpenEffect)
		if(request.form.get('pencilEffect')):
			pencilEffect= changeValue(pencilEffect)
		if(request.form.get('clearEffects')):
			clearEffects()

		return render_template("index.html")

def detect_motion(frameCount):
	global vs, outputFrame, lock, showIconInCorner,showDateTime,pixelEffect,sepiaEffect,sharpenEffect,pencilEffect
	total = 0

	# loop over frames from the video stream
	while True:
		frame = vs.read()
		frame = imutils.resize(frame, width=400)

		frameToModify = frame.copy()

		w,h= frame.shape[:2]

		if(showIconInCorner):
			logo = cv2.imread("icon.png")
			size = 100
			logo = cv2.resize(logo, (size, size))

			img2gray = cv2.cvtColor(logo, cv2.COLOR_BGR2GRAY)
			ret, mask = cv2.threshold(img2gray, 1, 255, cv2.THRESH_BINARY)

			roi = frameToModify[-h+size:+size, -size-1:-1]

			roi[np.where(mask)] = 0
			roi += logo

		if(showDateTime):
			timestamp = datetime.datetime.now()
			cv2.putText(frameToModify, timestamp.strftime(
			"%A %d %B %Y %I:%M:%S%p"), (10, frameToModify.shape[0] - 10),
			cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

		if(pixelEffect):
			temp = cv2.resize(frameToModify, (16, 16), interpolation=cv2.INTER_LINEAR)
			frameToModify = cv2.resize(temp, (frame.shape[:2]), interpolation=cv2.INTER_NEAREST)

		if(sepiaEffect):
			img_sepia = np.array(frameToModify, dtype=np.float64)
			img_sepia = cv2.transform(img_sepia, np.matrix([[0.272, 0.534, 0.131],
										[0.349, 0.686, 0.168],
										[0.393, 0.769, 0.189]]))
			img_sepia[np.where(img_sepia > 255)] = 255
			frameToModify = np.array(img_sepia, dtype=np.uint8)
			
		if(sharpenEffect):
			kernel = np.array([[-1, -1, -1], [-1, 9.5, -1], [-1, -1, -1]])
			temp = cv2.filter2D(frameToModify, -1, kernel)
			frameToModify=temp

		if(pencilEffect):
			sk_gray, sk_color = cv2.pencilSketch(frameToModify, sigma_s=60, sigma_r=0.07, shade_factor=0.1) 
			frameToModify=sk_gray


		frame = frameToModify
		total += 1
		with lock:
			outputFrame = frame.copy()

def generate():
	global outputFrame, lock
	while True:
		with lock:
			if outputFrame is None:
				continue
			(flag, encodedImage) = cv2.imencode(".jpg", outputFrame)
			if not flag:
				continue
		yield(b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + 
			bytearray(encodedImage) + b'\r\n')

@app.route("/video_feed")
def video_feed():
	return Response(generate(),
		mimetype = "multipart/x-mixed-replace; boundary=frame")


if __name__ == '__main__':

	frame=10
	ip="127.0.0.1"
	port="8002"
	t = threading.Thread(target=detect_motion, args=(
		frame,))
	t.daemon = True
	t.start()
	
	app.run(host=ip, port=port, debug=True,
		threaded=True, use_reloader=False)
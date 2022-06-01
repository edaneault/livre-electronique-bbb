import Adafruit_BBIO.GPIO as GPIO
import time

Next = "P8_14"
Home = "P8_16"
Back = "P8_18"
DEL_verte = "P9_21"
flag = 0

GPIO.setup(Next, GPIO.IN) 
GPIO.setup(Home, GPIO.IN) 
GPIO.setup(Back, GPIO.IN) 
GPIO.setup(DEL_verte, GPIO.OUT)

def Surprise(self):
	global flag
	
	if GPIO.input(Next):
		flag = 1
	else:
		flag = 0

GPIO.add_event_detect(Next, GPIO.FALLING, callback=Surprise, bouncetime=150)

while True:
	if flag == 1:
		GPIO.output(DEL_verte, 1)
		print("High")
		time.sleep(1)
	else:
		GPIO.output(DEL_verte, 0)
		print("Low")
		time.sleep(1)


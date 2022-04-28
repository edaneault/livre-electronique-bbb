import Adafruit_BBIO.GPIO as GPIO
import time

GPIO.setup("P8_14", GPIO.IN)
GPIO.setup("P9_21", GPIO.OUT)

while True:
	if GPIO.input("P8_14"):
		print("HIGH")
		GPIO.output("P9_21", 1)
	else:
		print("LOW")
		GPIO.output("P9_21", 0)
	time.sleep(1)

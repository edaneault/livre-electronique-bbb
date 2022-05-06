import Adafruit_BBIO.GPIO as GPIO
import time

B_Ar = "P8_14" 
B_Go = "P8_16"
B_Av = "P8_18"

x = ""
DEL_verte = "P9_21"
flag = 0
flag2 = 0
flag3 = 0

Ar = 0
Go = 0
Av = 0

GPIO.setup(B_Av, GPIO.IN)
GPIO.setup(B_Go, GPIO.IN)
GPIO.setup(B_Ar, GPIO.IN)
GPIO.setup(DEL_verte, GPIO.OUT)

def Surprise(self):
        global flag
        global flag2
        global flag3

        if GPIO.input(B_Ar):
                flag = 1
        else:
                flag = 0
        if GPIO.input(B_Ar):
                flag2 = 1
        else:
                flag2 = 0
        if GPIO.input(B_Ar):
                flag3 = 1
        else:
                flag3 = 0


GPIO.add_event_detect(B_Ar, GPIO.FALLING, callback=Surprise, bouncetime=150)
GPIO.add_event_detect(B_Go, GPIO.FALLING, callback=Surprise, bouncetime=150)
GPIO.add_event_detect(B_Av, GPIO.FALLING, callback=Surprise, bouncetime=150)

while True:

        for i in range(1000):
                if flag == 1: 
                        Ar = 1
                        print("S{:04d}".format(i)+"Ar{}".format(Ar) +"G{}".format(Go)+"Av{}".format(Av))
                        time.sleep(1)
                elif flag == 0:
                        Ar = 0
                        print("S{:04d}".format(i)+"Ar{}".format(Ar) +"G{}".format(Go)+"Av{}".format(Av))
                        time.sleep(1)
                if flag2 == 1: 
                        Go = 1
                        print("S{:04d}".format(i)+"Ar{}".format(Ar) +"G{}".format(Go)+"Av{}".format(Av))
                        time.sleep(1)
                elif flag2 == 0:
                        Go = 0
                        print("S{:04d}".format(i)+"Ar{}".format(Ar) +"G{}".format(Go)+"Av{}".format(Av))
                        time.sleep(1)
                if flag3 == 1: 
                        Av = 1
                        print("S{:04d}".format(i)+"Ar{}".format(Ar) +"G{}".format(Go)+"Av{}".format(Av))
                        time.sleep(1)
                elif flag3 == 0:
                        Av = 0
                        print("S{:04d}".format(i)+"Ar{}".format(Ar) +"G{}".format(Go)+"Av{}".format(Av))
                        time.sleep(1)


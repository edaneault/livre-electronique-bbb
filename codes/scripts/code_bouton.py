import Adafruit_BBIO.GPIO as GPIO
import time

infoPath = "/tmp/info-GPIO"

# Variables globales pour l'état de chacun des boutons
etatArriere = 0
etatGo = 0
etatAvant = 0

# Direction des GPIOs
pinArriere = "P9_11" 
pinGo = "P9_13"
pinAvant = "P9_15"
GPIO.setup(pinAvant, GPIO.IN)
GPIO.setup(pinGo, GPIO.IN)
GPIO.setup(pinArriere, GPIO.IN)

# Fonctions callback pour quand un bouton est pesé
def callbackBoutonArriere(self):
    global etatArriere
    etatArriere = 1
def callbackBoutonGo(self):
    global etatGo
    etatGo = 1
def callbackBoutonAvant(self):
    global etatAvant
    etatAvant = 1

# Configuration des callbacks
GPIO.add_event_detect(pinArriere, GPIO.FALLING, callback=callbackBoutonArriere, bouncetime=150)
GPIO.add_event_detect(pinGo,      GPIO.FALLING, callback=callbackBoutonGo,      bouncetime=150)
GPIO.add_event_detect(pinAvant,   GPIO.FALLING, callback=callbackBoutonAvant,   bouncetime=150)

while True:
    for i in range(1000):
        with open(infoPath, 'w') as file:
            file.write("S{:03d}".format(i)+"Ar{}".format(etatArriere) +"Go{}".format(etatGo)+"Av{}".format(etatAvant))
        etatArriere = 0
        etatGo = 0
        etatAvant = 0
        time.sleep(0.2)

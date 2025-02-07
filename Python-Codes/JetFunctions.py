import spidev
import time
import RPi.GPIO as GPIO


########################################
#   Open, use and close SPI ADC
########################################

########################################
# Do not forget to setup GPIO pins to SPI functions!
#
# Enter the followig commands into RPi terminal:
#
# raspi-gpio get
# raspi-gpio set 9 a0
# raspi-gpio set 10 a0
# raspi-gpio set 11 a0
# raspi-gpio get
########################################

spi = spidev.SpiDev()

def initSpiAdc():
    spi.open(0, 0)
    spi.max_speed_hz = 1600000
    print ("SPI for ADC has been initialized")

def deinitSpiAdc():
    spi.close()
    print ("SPI cleanup finished")

def getAdc():
    adcResponse = spi.xfer2([0, 0])
    return ((adcResponse[0] & 0x1F) << 8 | adcResponse[1]) >> 1


########################################
#   Setup and use GPIO for step motor
########################################

directionPin = 27
enablePin = 22
stepPin = 17

def initStepMotorGpio():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup([directionPin, enablePin, stepPin], GPIO.OUT)
    print ("GPIO for step motor have been initialized")

def deinitStepMotorGpio():
    GPIO.output([directionPin, enablePin, stepPin], 0)
    GPIO.cleanup()
    print ("GPIO cleanup finished")

def step():
    GPIO.output(stepPin, 0)
    time.sleep(0.005)
    GPIO.output(stepPin, 1)
    time.sleep(0.005)
    
def stepForward(n):
    GPIO.output(directionPin, 1)
    GPIO.output(enablePin, 1)

    for i in range(n):
        step()

    GPIO.output(enablePin, 0)

def stepBackward(n):
    GPIO.output(directionPin, 0)
    GPIO.output(enablePin, 1)

    for i in range(n):
        step()

    GPIO.output(enablePin, 0)
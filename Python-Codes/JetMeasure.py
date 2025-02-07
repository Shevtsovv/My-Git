import jetFunctions as j
import numpy as np
import time

j.initSpiAdc()
j.initStepMotorGpio()
with open('preasure100.txt', 'w') as f:
    for i in range(1000):
        j.stepForward(1)
        if (i % 10) == 0:
            f.write(str(j.getAdc()) + '\n')

j.stepBackward(1000)

j.deinitSpiAdc()
j.deinitStepMotorGpio()

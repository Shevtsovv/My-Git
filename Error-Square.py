#Расчет среднего квадратичного отклонения

import numpy as np
import matplotlib.pyplot as plt
x = []
with open("Error-Measure.txt", "r") as measure:
    for line in measure:
        s = line.split(" ")
        x.append(float(s[0]))
u = np.array(x)
n = len(u)
print("Количество измерений: ", n)
#Среднее квадратичное отклонение - это разброс значений случайной величины 
u_average = np.mean(np.array(x))
print("Среднее значение измерений величины: ", u_average)
sigma_u = np.sqrt(np.mean((u - u_average)**2)/(n - 1))
print("Разброс значений величины: ", sigma_u)

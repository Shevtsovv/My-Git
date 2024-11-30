import matplotlib.pyplot as plt
import numpy as np
x = []
y = []
z = []
with open("Weight.txt", "r") as weight:
    for line in weight:
        s = line.split(" ")
        z.append(float(s[0])) #столбик с массой

with open("Omega.txt", "r") as omega:
    for line in omega:
        s = line.split(" ")
        x.append(float(s[0])) #столбик с временем
        y.append(float(s[1])) #столбик с номером оборотов     
t = np.array(x) #время n-оборотов
N = np.array(y) #число оборотов
m = np.array(z)
omega = (2*np.pi*N)/t #скорость прецесии, с-1

alpha = 1.2
moment_power = m*alpha

coefficient = np.polyfit(moment_power, omega, 1)
p = np.poly1d(coefficient)
plt.title("Зависимость скорости прецессии от момента силы")
plt.xlabel("Момент силы, Н*м")
plt.ylabel("Скорость прецессии гироскопа, с-1")
plt.grid(visible = True, which = "major", linewidth = 1.2, linestyle = "-", color = "lightgray")
plt.grid(visible = True, which = "minor", linewidth = 1.2, linestyle = "--", color = "lightgray")
plt.scatter(moment_power, omega, color = "blue")
plt.plot(moment_power, p(moment_power), linestyle = "-", color = "black")
plt.legend(["Аппроксимирующая прямая"])
plt.savefig("Прецессия и момент силы")

plt.show()




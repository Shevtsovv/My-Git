import matplotlib.pyplot as plt
import numpy as np

plt.figure(figsize=(10,6))
files = ["12.txt", "23.txt", "34.txt", "41.txt"]
colors = ["red", "green", "blue", "orange"]
labels = ["Изотерма 1-2", "Адиабата 2-3", "Изотерма 3-4","Адиабата 4-1"]

cua = ["cua.txt"]

for file, color, label in zip(files, colors, labels):
    v, p = np.loadtxt(file, unpack=True)
    plt.plot(v, p, color=color, label=label)
for data in cua:
    theta, A_cycle, Q_heat, Q_cooler = np.loadtxt("cua.txt", unpack=True)
    plt.text(7, 90000, f"Совершена работа: A = {A_cycle} Дж \nCUA: η = {theta} \nПолучено: Q_{12} = {Q_heat} Дж\nОтдано: Q_{34} = {Q_cooler} Дж",
            bbox=dict(facecolor='white', alpha=0.8), fontsize = 11)

plt.xlabel("Объем, $м^3$")
plt.ylabel("Давление,Па")

plt.title("Цикл Карно")
plt.legend()

plt.grid(True)
plt.minorticks_on()
plt.show()
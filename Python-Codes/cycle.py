import matplotlib.pyplot as plt
import numpy as np

plt.figure(figsize=(10,6))
files = ["12.txt", "23.txt", "34.txt", "41.txt"]
colors = ["red", "green", "blue", "orange"]
labels = ["Изотермическое расширение", "Адиабатическое расширение", "Изотермическое сжатие", "Адиабатическое сжатие"]

cua = ["cua.txt"]

for file, color, label in zip(files, colors, labels):
    v, p = np.loadtxt(file, unpack=True)
    plt.plot(v, p, color=color, label=label)
for data in cua:
    theta, A_cycle = np.loadtxt("cua.txt", unpack=True)
    plt.text(7, 90000, f"A = {A_cycle} Дж \nη = {theta}", bbox=dict(facecolor='white', alpha=0.8))

plt.xlabel("Объем, $м^3$")
plt.ylabel("Давление,Па")

plt.title("Цикл Карно")
plt.legend()

plt.grid(True)
plt.minorticks_on()
plt.show()
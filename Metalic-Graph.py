import matplotlib.pyplot as plt
import numpy as np
x = []
y = []
with open("Duralumin.txt", "r") as steel:
    for line in steel:
        s = line.split(" ")
        x.append(float(s[0]))
        y.append(float(s[1]))
n = np.array(x)
f = np.array(y)
coefficients = np.polyfit(n, f, 1)
p = np.poly1d(coefficients)
plt.title("Зависимость резонансной частоты от номера измерений для дюраля")
plt.xlabel("Номер измерения")
plt.ylabel("Резонансная частота, кГц")
plt.minorticks_on()
plt.grid(visible = True, which = "major", linewidth = 1.2, linestyle = "-", color = "lightgray")
plt.grid(visible = True, which = "minor", linewidth = 1.2, linestyle = "--", color = "lightgray")
plt.plot(n, p(n), linestyle = "-", color = "black")
plt.legend(["Аппроксимирующая прямая"])
plt.scatter(n, f, color = "blue")
plt.savefig("Duralumin-Line.png")
plt.show()

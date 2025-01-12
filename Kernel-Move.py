import numpy as np
import matplotlib.pyplot as plt
x = []
y = []
with open("kernel.txt", "r") as kernel:
    for line in kernel:
        s = line.split(" ")
        x.append(float(s[0]))
        y.append(float(s[1]))
t = np.array(x)
v = np.array(y)
# Коэффициенты
coefficients = np.polyfit(t, v, 1)
print("Linear Fit Coefficients:", coefficients)
# Cоздаем аппроксимирующую прямую
p = np.poly1d(coefficients)
plt.title("Стержень и его отрыв от вертикальной стенки")
plt.minorticks_on()
plt.grid(visible = True, which = "major", linewidth = 1.2, linestyle = "-", color = "lightgray")
plt.xlabel("sin(a0)")
plt.ylabel("sin(a)")
plt.grid(visible = True, which = "minor", linewidth = 1.2, linestyle = "--", color = "lightgray")
plt.plot(t, p(t), linestyle = "-", color = "black")
plt.legend(["y = 0.66x + 0.007"])
plt.scatter(t, v, color = "blue")
plt.savefig("Kernel-Move.png")
plt.show()


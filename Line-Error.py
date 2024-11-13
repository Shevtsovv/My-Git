import numpy as np
import matplotlib.pyplot as plt
x = []
y = []
with open("approcs.txt", "r") as app:
    for line in app:
        s = line.split(" ")
        x.append(float(s[0]))
        y.append(float(s[1]))
t = np.array(x)
v = np.array(y)
# Коэффициенты
coefficients = np.polyfit(t, v, 1)
#print("Linear Fit Coefficients:", coefficients)
# Cоздаем аппроксимирующую прямую
p = np.poly1d(coefficients)
plt.plot(t, p(t), linestyle = "-", color = "black")
plt.scatter(t, v, color = "blue")
plt.title("Заголовок для графика")
plt.minorticks_on()
plt.grid(visible = True, which = "major", linewidth = 1.2, linestyle = "-", color = "lightgray")
plt.xlabel("Измерение по оси абцисс")
plt.ylabel("Измерение по оси ординат")
plt.grid(visible = True, which = "minor", linewidth = 1.2, linestyle = "--", color = "lightgray")
plt.plot(t, p(t))
plt.legend()
plt.show()

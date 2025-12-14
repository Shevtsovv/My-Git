import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
def foo(x, a, b):
    return (a * x) + b
m = []
Re = []

with open("Spectrum/a1a2.txt", "r") as amplitude:
    for line in amplitude:
        s = line.split(" ")
        m.append(float(s[0]))
        Re.append(float(s[1]))
m_x = np.array(m)
Re_y = np.array(Re)
R = np.array([0.095, 0.14, 0.188, 0.239, 0.284, 0.338, 0.383, 0.434, 0.483])
popt, pcov = curve_fit(foo, m_x, R/2)
y_fit = foo(m_x, *popt)
fig = plt.figure(figsize=(10, 6))
print(R/2, y_fit/2)
plt.scatter(m_x, R/2, label=f'Отношение амплитуд', color='blue', zorder=5)
plt.plot(m_x, y_fit, color='red', label=f'Аппроксимация y = {popt[0]:.3f}x + {popt[1]:.3f}')
plt.grid(visible=True, which='minor', linewidth=0.9)
plt.grid(visible=True, which='major', linewidth=0.9)
plt.minorticks_on()
plt.legend()
plt.title('Отношение боковой и центральной амплитуды для разной глубины модуляции')
plt.xlabel('Глубина модуляции')
plt.ylabel('Отношение амплитуд')
plt.savefig("am_approx.png")

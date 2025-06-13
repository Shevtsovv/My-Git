import matplotlib.pyplot as plt
import numpy as np

plt.figure(figsize=(12, 6))

files = ["12.txt", "23.txt", "34.txt", "41.txt"]
colors = ["blue", "red", "green", "orange"]
labels = ["Изотерма 1-2", "Адиабата 2-3", 
          "Изотерма 3-4", "Адиабата 4-1"]
cua_data = np.loadtxt("cua.txt")
theta, A_cycle, Q_heat, Q_cooler, t_heat, t_cold = cua_data

plt.subplot(1, 2, 1)
for file, color, label in zip(files, colors, labels):
    data = np.loadtxt(file)
    v, p = data[:, 0], data[:, 1]
    plt.plot(v, p, color=color, label=label, linewidth = 2.5)
    
plt.xlabel("Объём, $м^3$")
plt.ylabel("Давление, Па")
plt.title("Цикл Карно: P-V диаграмма")
plt.legend()
plt.grid(True)

plt.subplot(1, 2, 2)
for file, color, label in zip(files, colors, labels):
    data = np.loadtxt(file)
    s, t = data[:, 3], data[:, 2]
    plt.plot(s, t, color=color, label=label, linewidth = 2.5)
plt.figtext(0.5, 0.02,
    f"Работа газа: $A = {A_cycle}$ Дж\nКПД: $\eta = {theta}$\nПолучено тепла: $Q_+ = {Q_heat}$ Дж\nОтдано тепла: $Q_- = {Q_cooler}$ Дж\n"
    f"$T_+ = {t_heat}$ К\n$T_- = {t_cold}$ К",
    ha = 'center', bbox=dict(facecolor = 'white', alpha = 0.8), fontsize = 11)
plt.xlabel("Энтропия, $Дж/К$")
plt.ylabel("Температура, К")
plt.title("Цикл Карно: T-S диаграмма")
plt.legend()
plt.grid(True)
plt.show()
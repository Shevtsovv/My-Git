import matplotlib.pyplot as plt
import numpy as np

# Данные из файла: [I_P(мА), T(К), n]
data = np.array([
    [1.513, 49158, 3.33],
    [3.101, 43882, 6.16],
    [4.005, 39864, 7.93],
    [5.000, 38726, 9.4]
])

# Извлекаем столбцы
I_P = data[:, 0]  # ток разряда (мА)
T = data[:, 1]    # температура (К)
n = data[:, 2]    # концентрация заряженных ионов

# Создаем графики
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

# График 1: Зависимость температуры от тока разряда T(I_P)
ax1.plot(I_P, T, 'bo-', linewidth=2, markersize=8, label='Экспериментальные точки')
ax1.set_xlabel('Ток разряда I_P, мА', fontsize=12)
ax1.set_ylabel('Температура T, К', fontsize=12)
ax1.set_title('Зависимость температуры плазмы \nот тока разряда T(I_P)', fontsize=14)
ax1.grid(True, alpha=0.3)
ax1.legend()

# График 2: Зависимость концентрации от тока разряда n(I_P)
ax2.plot(I_P, n, 'ro-', linewidth=2, markersize=8, label='Экспериментальные точки')
ax2.set_xlabel('Ток разряда I_P, мА', fontsize=12)
ax2.set_ylabel('Концентрация n', fontsize=12)
ax2.set_title('Зависимость концентрации ионов \nот тока разряда n(I_P)', fontsize=14)
ax2.grid(True, alpha=0.3)
ax2.legend()

# Улучшаем внешний вид
plt.tight_layout()
plt.savefig("last.png")

# Дополнительно: вывод данных в табличной форме
print("Данные из файла:")
print("I_P(мА)\tT(К)\tn")
for i in range(len(data)):
    print(f"{data[i, 0]:.3f}\t{data[i, 1]}\t{data[i, 2]:.2f}")
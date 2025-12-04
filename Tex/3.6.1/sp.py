import numpy as np
import matplotlib.pyplot as plt

# Чтение данных из файла
data = np.loadtxt('Spectrum/speklt_E.txt', skiprows=2)  # skiprows=1 чтобы пропустить заголовок

# Извлечение данных
freq = data[:, 0]    # Частота в МГц
chA = data[:, 1]     # Канал A в мВ
chB = data[:, 2]     # Канал B в В

# Создание графика
plt.figure(figsize=(12, 6))

# График Канала A (мВ)
plt.plot(freq, chA, 'b-', label='Канал A (мВ)', linewidth=1)

# График Канала B (В) 
# Умножаем на 1000 для перевода в мВ для наглядности сравнения
plt.plot(freq + 0.1, chB * 100, 'r-', label='Канал B (мВ)', linewidth=1)

# Настройки осей
plt.xlabel('Частота (МГц)')
plt.ylabel('Амплитуда')
plt.title('Спектры сигналов до и после RC-фильтра')
plt.legend()
plt.grid(True)

# Автоматическое масштабирование
plt.autoscale(enable=True, axis='both', tight=True)

plt.savefig('rc.png')


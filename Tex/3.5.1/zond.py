import matplotlib.pyplot as plt
import numpy as np
# Чтение данных из файла
with open('txt/zond.txt', 'r') as file:
    data = file.readlines()
# Парсинг данных
currents = []  # будет содержать 4 списка токов
voltages = []  # будет содержать 4 списка напряжений
for line in data:
    values = list(map(float, line.strip().split()))
    
    # Разделяем на 4 кривые
    for i in range(4):
        if len(currents) <= i:
            currents.append([])
            voltages.append([])
        voltage = values[i*2]
        current = values[i*2 + 1]
        voltages[i].append(voltage)
        currents[i].append(current)
discharge_currents = [5.000, 4.005, 3.101, 1.513]
# plt.figure(figsize=(10, 6))
colors = ['red', 'blue', 'green', 'orange']
markers = ['o', 's', '^', 'd']
for i in range(4):
    plt.scatter(voltages[i], currents[i], marker=markers[i], color=colors[i], label=f'$I_p$ = {discharge_currents[i]} мА')
plt.xlabel('Напряжение на зонде, U (В)')
plt.ylabel('Ток зонда, I (мА)')
plt.title('Вольт-амперные характеристики двойного зонда')
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()
plt.savefig('zond.png')
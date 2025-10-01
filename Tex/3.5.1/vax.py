import matplotlib.pyplot as plt
import numpy as np
with open('txt/vax.txt', 'r') as file:
    data = file.readlines()
current = []
voltage = []
for line in data:
    values = line.strip().split()
    if len(values) == 2:
        current.append(float(values[0]))
        voltage.append(float(values[1]))
mid_point = len(current) // 2
current_forward = current[:mid_point]
voltage_forward = voltage[:mid_point]
current_backward = current[mid_point:]
voltage_backward = voltage[mid_point:]
# Метод 1: Численное дифференцирование для прямой ветви
def dif(currents, voltages):
    # Сортируем по току для корректного дифференцирования
    sorted_indices = np.argsort(currents)
    currents_sorted = np.array(currents)[sorted_indices]
    voltages_sorted = np.array(voltages)[sorted_indices]
    # Численная производная dU/dI
    dU_dI = np.gradient(voltages_sorted, currents_sorted)
    # Находим точку с минимальным dU/dI (наименьшее сопротивление)
    min_resistance_idx = np.argmin(dU_dI)
    return currents_sorted, voltages_sorted, dU_dI, min_resistance_idx
# Анализируем прямую ветвь (увеличение тока)
I_sorted, U_sorted, dU_dI, min_idx = dif(current_forward, voltage_forward)
min_R_dif = dU_dI[min_idx] * 1000
min_current = I_sorted[min_idx]
min_voltage = U_sorted[min_idx]
print(f"Минимальное дифференциальное сопротивление R_dif = {min_R_dif:.3f} Ом")
print(f"В точке: I = {min_current:.2f} А, U = {min_voltage:.2f} В")
# Основной график ВАХ
plt.plot(voltage_forward, current_forward, marker='o', linewidth=1.2, 
         linestyle='-', label='Увеличение тока', color='blue')
plt.plot(voltage_backward, current_backward, marker='s', linewidth=1.2, linestyle='-', label='Уменьшение тока', color='red')
plt.plot(min_voltage, min_current, marker = '*', markersize=10, label=f'dU/dI: {min_R_dif:.2f} Ом')
plt.xlabel('Напряжение, В')
plt.ylabel('Ток, мА')
plt.title('Вольт-амперная характеристика газового разряда')
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.legend()
plt.savefig('vax.png')
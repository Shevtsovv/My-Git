import matplotlib.pyplot as plt
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
ignition_voltage = 15.20
ignition_current = 4.02
# Добавляем аннотацию к точке
plt.plot(voltage_forward, current_forward, marker = 'o', linewidth=1.2, linestyle = 'solid', label='Увеличение тока')
plt.plot(voltage_backward, current_backward, marker = 's', linewidth=1.2, linestyle = 'solid', label='Уменьшение тока')
plt.xlabel('Напряжение, В')
plt.ylabel('Ток, А')
plt.title('Вольт-амперная характеристика газового разряда')
plt.grid(True, alpha=0.3)
plt.legend()
# Показываем график
plt.tight_layout()
plt.savefig('vax.png')
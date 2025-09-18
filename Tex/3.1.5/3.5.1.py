import matplotlib.pyplot as plt
import numpy as np
i = []
u = []
with open('txt/vax.txt', 'r') as vax:
    for line in vax:
        s = line.split()
        i.append(float(s[0]))
        u.append(float(s[1]))
I = np.array(i)
U = np.array(u)
c = np.polyfit(U, I, 3)
poly = np.poly1d(c)
plt.figure(figsize=(14, 7))
plt.scatter(U, I, s=25)
plt.plot(U, poly(U), 'r-', linewidth=1.2, label='ВАХ газового разряда')
plt.xlabel('Напряжение, В')
plt.ylabel('Ток, мА')
plt.grid(visible = True, which = 'major', linewidth = 1.2)
plt.grid(visible = True, which = 'minor', linewidth = 1.2)
plt.minorticks_on()
plt.legend()
plt.title('Вольт-амперная характеристика газового разряда')
plt.savefig('vax.png')
import matplotlib.pyplot as plt
import numpy as np
data = np.loadtxt('txt/zond.txt')
markers = ['o', 's', '^', 'D']
amperas = ['$5.000\pm 0.001$', '$4.005\pm 0.001$', '$3.101\pm 0.001$', '$1.513\pm 0.001$']
plt.figure(figsize=(10, 6))
for i in range(0, data.shape[1], 2):
    if i + 1 < data.shape[1]:
        x = data[:, i]
        y = data[:, i+1]
        plt.plot(x, y, label=f'Ток разряда {amperas[i//2]}', marker=markers[i//2], linewidth=1.2, markersize=5)
plt.xlabel('Напряжение, В')
plt.ylabel('Сила тока, А')
plt.title('Зондовые характеристики при разных токах разряда')
plt.legend()
plt.grid(True, which='major', linewidth=1.2)
plt.grid(True, which='minor', linewidth=1.2)
plt.minorticks_on()
plt.savefig('zond.png')

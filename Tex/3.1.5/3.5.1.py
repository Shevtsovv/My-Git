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
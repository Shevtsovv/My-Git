#Построение 'смешанных' графиков с помощью метода np.vectorize

import numpy as np
import matplotlib.pyplot as plt

def spooky_line(x):
    y = x**(1/x)
    return y
y = np.vectorize(spooky_line) #np.vectorize — преобразует алгоритм, работающего с одним значением за раз, в работу с набором значений (вектором) за один раз.
x = np.arange(1, 5.1, 0.1)

def lin_ls(u):
    v = 0.5*u 
    return v
v = np.vectorize(lin_ls)
u = np.arange(1, 5.1, 0.1)

plt.grid(visible = True, which="major", linewidth=1.2, linestyle="-", color="lightgrey")
plt.grid(visible=True, which="minor",linewidth=1.2, linestyle="--", color="lightgrey")
plt.minorticks_on()
plt.title("Смешанный график")
plt.xlabel("Измерения x, единица измерения")
plt.ylabel("Измерение y, единица измерения")
plt.plot(x, y(x), color = "black", marker = ".")
plt.plot(u, v(u), color = "blue", marker = ".")
#plt.legend(["Кривая"])
plt.show()
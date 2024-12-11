import matplotlib.pyplot as plt
import numpy as np

y = np.array([40/0.11748, 80/0.20721, 120/0.28354, 160/0.35065, 200/0.41042])
x = np.array([0.11748, 0.20721, 0.28354, 0.35065, 0.41042])
coefficients = np.polyfit(x, y, 1)
np.poly1d(coefficients)
print(coefficients)
p = np.poly1d(coefficients)
plt.plot(x, p(x), linestyle = "-", color = "black")
plt.scatter(x, y)
plt.title("Определение коэффициента ускорения свободного падения")
plt.minorticks_on()
plt.grid(visible = True, which = "major", linewidth = 1.2, linestyle = "-", color = "lightgray")
plt.xlabel("gt/2, см/с")
plt.ylabel("nl/t, см/с")
plt.grid(visible = True, which = "minor", linewidth = 1.2, linestyle = "--", color = "lightgray")
plt.legend(["y = 498x + 282"])
plt.savefig("Ускорение свободного падения.png")
plt.show()







     


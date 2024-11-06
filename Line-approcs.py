import numpy as np
import matplotlib.pyplot as plt
x = []
y = []
with open("approcs.txt", "r") as app:
    for line in app:
        s = line.split(" ")
        x.append(float(s[0]))
        y.append(float(s[1]))
t = np.array(x)
v = np.array(y)

# Perform linear fit
coefficients = np.polyfit(t, v, 1)
#print("Linear Fit Coefficients:", coefficients)

# Create polynomial function
p = np.poly1d(coefficients)
plt.plot(t, v, linestyle = " ", color = "orange", marker = ".")
#plt.scatter(t, v, label="Data Points")
plt.minorticks_on()
plt.grid(visible = True, which = "major", linewidth = 1.2, linestyle = "-", color = "lightgray")
plt.xlabel("Измерение по оси абцисс")
plt.ylabel("Измерение по оси ординат")
plt.grid(visible = True, which = "minor", linewidth = 1.2, linestyle = "--", color = "lightgray")
plt.plot(t, p(t))
plt.legend()
plt.show()

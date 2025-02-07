import matplotlib.pyplot as plt
import numpy as np

with open("settings.txt", "r") as settings:
    num = [float(i) for i in settings.read().split("\n")]
#print(num)
data_array = np.loadtxt("data.txt", dtype = (int))
voltage = data_array * 0.013
U = voltage
#print(voltage)
delta_time = 0.011
n = 897
time_measure = np.array(range(0, int(n)+1))
time = time_measure * delta_time
#print(time, " ")
t = time
plt.grid(visible = True, which="major", linewidth=1.2, linestyle="-", color="lightgrey")
plt.grid(visible=True, which="minor",linewidth=1.2, linestyle="--", color="lightgrey")

plt.text(6,2, "Время зарядки: " +str(4.2) + "с" +"\n" + "\n" "Время разрядки: " +str(5.5) + "с", fontsize="large", fontstyle="normal")
plt.minorticks_on()
plt.title("График зависимости напряжения от времени U(t)")
plt.xlabel("Время измерения, с")
plt.ylabel("Значение напряжения, В")
plt.plot(t, U, marker='.',linewidth=0.7, color='blue')
plt.legend(["U(t)"])
plt.savefig("Показатели ADC.png")
plt.show()

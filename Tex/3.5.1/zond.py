import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np
with open('txt/zond.txt', 'r') as file:
    data = file.readlines()
currents = []
voltages = []
for line in data:
    values = list(map(float, line.strip().split()))
    for i in range(4):
        if len(currents) <= i:
            currents.append([])
            voltages.append([])
        voltage = values[i*2]
        current = values[i*2 + 1]
        voltages[i].append(voltage)
        currents[i].append(current)
discharge_currents = [5.000, 4.005, 3.101, 1.513]
colors = ['red', 'blue', 'green', 'orange']
markers = ['o', 's', '^', 'd']
def tanh_fit(U, I_sat, alpha, I_0):
    return I_sat * np.tanh(alpha * U) + I_0
def tanh_fit_simple(U, I_sat, alpha):
    return I_sat * np.tanh(alpha * U)
for i in range(4):
    V = np.array(voltages[i])
    I = np.array(currents[i])
    I_sat_guess = max(abs(np.min(I)), abs(np.max(I)))
    alpha_guess = 0.1
    I_0_guess = 0.0
    try:
        popt, pcov = curve_fit(tanh_fit, V, I, p0=[I_sat_guess, alpha_guess, I_0_guess], maxfev=5000)
        I_sat, alpha, I_0 = popt
        V_smooth = np.linspace(min(V), max(V), 300)
        I_smooth = tanh_fit(V_smooth, *popt)
        plt.scatter(V, I, marker=markers[i], color=colors[i], alpha=0.7, label=f'$I_p$ = {discharge_currents[i]} мА (данные)')
        plt.plot(V_smooth, I_smooth, color=colors[i], linewidth=2)
        e = 1.602e-19
        k = 1.381e-23
        T_e = e / (2 * k * alpha)
        T_e_eV = T_e * k / e
        print(f"Параметры для I_p = {discharge_currents[i]} мА:")
        print(f"  I_sat = {I_sat:.2f} мА")
        print(f"  α = {alpha:.4f} В⁻¹")
        print(f"  I_0 = {I_0:.2f} мА")
        print(f"  T_e = {T_e:.0f} K = {T_e_eV:.2f} эВ")
        print()
    except Exception as e:
        print(f"Ошибка аппроксимации для I_p = {discharge_currents[i]} мА: {e}")
        try:
            popt, pcov = curve_fit(tanh_fit_simple, V, I, p0=[I_sat_guess, alpha_guess], maxfev=5000)
            I_sat, alpha = popt
            V_smooth = np.linspace(min(V), max(V), 300)
            I_smooth = tanh_fit_simple(V_smooth, *popt)
            plt.scatter(V, I, marker=markers[i], color=colors[i], alpha=0.7)
            plt.plot(V_smooth, I_smooth, color=colors[i], linewidth=2)
            e = 1.602e-19
            k = 1.381e-23
            T_e = e / (2 * k * alpha)
            T_e_eV = T_e * k / e
            print(f"Параметры (упрощенная форма) для I_p = {discharge_currents[i]} мА:")
            print(f"  I_sat = {I_sat:.2f} мА")
            print(f"  α = {alpha:.4f} В⁻¹")
            print(f"  T_e = {T_e:.0f} K = {T_e_eV:.2f} эВ")
            print()
        except Exception as e2:
            print(f"Ошибка и в упрощенной форме: {e2}")
plt.xlabel('Напряжение на зонде, U (В)')
plt.ylabel('Ток зонда, I (мА)')
plt.title('Вольт-амперные характеристики двойного зонда')
plt.grid(True, alpha=0.3)
plt.legend()
plt.axhline(y=0, color='black', linewidth=0.5, linestyle='--', alpha=0.5)
plt.axvline(x=0, color='black', linewidth=0.5, linestyle='--', alpha=0.5)
plt.tight_layout()
# plt.savefig('zond.png', dpi=300)
# plt.show()

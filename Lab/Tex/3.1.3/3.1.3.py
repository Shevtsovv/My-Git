import matplotlib.pyplot as plt
import numpy as np
# n = np.array([3, 4, 5, 6, 7, 8, 9, 10, 11, 12])
# T = np.array([1.067, 1.418, 1.600, 2.341, 2.678, 2.834, 3.450, 4.234, 4.169, 5.350])
# coeff, cov = np.polyfit(n, T, 1, cov=True)
# errors_coeff = np.sqrt(np.diag(cov))
# funcion_style = np.poly1d(coeff)
# T_err = np.std(T, ddof=1)
plt.figure(figsize=(12, 8))
# plt.title("Зависимость крутильного периода от количества шариков цепочки")
# plt.grid(visible=True, which='major', linewidth=1.2)
# plt.grid(visible=True, which='minor', linewidth=0.5)
# plt.minorticks_on()
# plt.plot(n, funcion_style(n), 'r-', label=f'{funcion_style}', linewidth=2)
# plt.errorbar(n, T, yerr=T_err, fmt="o", capsize=4, capthick=2, markersize=4, label='Экспериментальные точки')
# plt.legend()
# plt.xlabel("Число шариков")
# plt.ylabel("Период крутильных колебаний, с")
# plt.tight_layout()
# plt.savefig("period.png", dpi=300)
n = np.array([4, 6, 8, 10, 12])
m_extra = [0.356, 0.201, 0.176, 0.227, 0.146]
x = [0.59, 1.18, 1.77, 2.4, 2.95]
g = 980
mxr = []
for i in range(0, len(n)):
    mxr.append(m_extra[i] * x[i] * g)
# coeff, cov = np.polyfit(n, mxr, 1, cov = True)
# def line_ls(parameter1, res = []):
#     p, q = parameter1
#     for item in n:
#         res.append(p * item + q)
#     return res
# errors = np.sqrt(np.diag(cov))
# print(coeff, errors)
# func = np.poly1d(coeff)
# plt.scatter(n, mxr)
coeff = np.polyfit(n, mxr, 1)
function_style = np.poly1d(coeff)
M_err = np.std(mxr, ddof=1)
plt.errorbar(n, mxr, yerr=M_err, fmt="o", capsize=4, capthick=2, markersize=4, label='Экспериментальные точки')
plt.title("Определение $B_{\perp}$")
plt.grid(visible = True, which = 'major', linewidth = 1.2)
plt.grid(visible = True, which = 'minor', linewidth = 1.2)
plt.plot(n, function_style(n), 'r-', label = f'{function_style}', linewidth=2)
plt.legend()
plt.xlabel("Число шариков (Четное)")
plt.ylabel("Произведение $m_{x}\cdot x$, $г\cdot см^2/с^2$")
plt.savefig("vertical.png", dpi=300)
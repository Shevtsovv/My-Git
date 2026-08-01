import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(-5,5, 100)
y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(x, y)
Z = np.sin(np.sqrt(X**2 + Y**2))
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(projection='3d')
surf = ax.plot_surface(X, Y, Z, cmap='plasma', edgecolor='black', linewidth=0.5)
fig.colorbar(surf)
plt.show()
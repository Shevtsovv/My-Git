import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
z=np.linspace(-150, 150, 1)
theta=np.linspace(-4*np.pi, 4*np.pi, 100)
r=6400
x=r*np.cos(theta)
y=r*np.sin(theta)
ax.plot(x, y, z, label='3d Graph')
ax.legend()
#plt.savefig("Satellite appearance.png")
plt.show()
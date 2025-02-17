import numpy as np
import matplotlib.pyplot as plt

#Constants
G = 6.67430e-11  #Gravitational constant 
M = 5.972e24     #Mass of the Earth
mu = G * M       #Standard gravitational parameter

#Initial conditions
r0 = np.array([7e6, 0])       #Initial position vector (m) 
v0 = np.array([0, 7500])      #Initial velocity vector (m/s)

#Time parameters
dt = 1                         #Time step (s)
t_total = 6000                 #Total simulation time (s)
num_steps = int(t_total / dt)  #Number of steps

# Arrays to store position and velocity
r = np.zeros((num_steps, 2))   # Position array [x, y]
v = np.zeros((num_steps, 2))   # Velocity array [vx, vy]

# Set initial conditions
r[0] = r0
v[0] = v0

# Numerical integration (Euler's method)
for i in range(1, num_steps):
    # Calculate the distance from the center
    #The norm shape of vector
    distance = np.linalg.norm(r[i-1])
    
    # Calculate the acceleration due to gravity
    a = -mu * r[i-1] / distance**3
    
    # Update velocity and position
    v[i] = v[i-1] + a * dt
    r[i] = r[i-1] + v[i] * dt

# Plot the orbit
plt.figure(figsize=(8, 5))
plt.plot(r[:, 0], r[:, 1], label="Орбита спутника")
plt.plot(0, 0, '*', label="Земля")  # Earth at the center
plt.xlabel("Координата x (m)")
plt.ylabel("Координата y (m)")
plt.title("Орбита спутника вокруг Земли")
plt.legend()
plt.grid(True)
plt.axis("equal")
plt.savefig("EllipsSatel.png")
plt.show()
import matplotlib.pyplot as plt
import numpy as np

def calculate_hyper(x0,y0,v0,GM=398600.4415,NUM=100):
    #Main conditions for satellite
    r0 = np.sqrt(x0**2+y0**2)
    v0satelx=0
    v0sately=v0

    #Statement for satellite's energy. For ellips energy>0
    energy = (v0satelx**2+v0sately**2)/2-GM/r0
    if(energy<=0):
        print("This is not hyperbol trajectory.")
        return None
    
    #Calculating
    a=-GM/(2*energy)
    h=x0*v0sately-y0*v0satelx
    eccentricity=np.sqrt(1+(2*energy*h**2)/(GM**2))
    rang=np.arccos(-1/eccentricity)
    gamma=np.linspace(-0.95*rang, 0.95*rang, NUM)
    r = a*(eccentricity**2-1)/(1+eccentricity*np.cos(gamma))
    x_rot=r*np.cos(gamma)
    y_rot=r*np.sin(gamma)
    x=x_rot
    y=y_rot
    return x,y 

def trajectory(x,y,x0,y0):
    if x is not None and y is not None:
        plt.plot(x,y)
        plt.plot(x0,y0)
        plt.plot(0,0, marker="*", color="green")
        plt.title("Гиперболическая траектория спутника")
    plt.xlabel("x, (км)")
    plt.ylabel("y, (км)")
    plt.grid(visible=True, which="major", linewidth=1.2, color="lightgray", linestyle="--")
    plt.grid(visible=True, which="minor", linewidth=1.2, color="lightgray", linestyle="-")
    plt.savefig("satellite.png")
    plt.show()

#It's working
x0=7000
y0=0
v0=11.7
x,y=calculate_hyper(x0,y0,v0)
trajectory(x,y,x0,y0)






import astropy as astropy
import skyfield.api as api
from skyfield.api import EarthSatellite as EarthSatellite
from skyfield.api import load as load
from skyfield.api import wgs84 as wgs84
from skyfield.api import N,W
import numpy as np
import matplotlib.pyplot as plt

longitude = 37.5
latitude = 53.93
sea_hight = 300
ts = load.timescale()               
line1 = "33591U 09005A   25048.91581445  .00000350  00000+0  21073-3 0  9994"
line2 = "33591  99.0129 112.9305 0013041 321.9958  38.0293 14.13287479826074"
satellite = EarthSatellite(line1, line2, "NOAA 19", ts)
t = ts.now()
geocentre = satellite.at(t)
print(geocentre)
print("Position components(NOAA19): ", geocentre.position.km)
print("Velocity components(NOAA19): ", geocentre.velocity.km_per_s)
print("Full velocity(NOAA19): ", geocentre.speed().km_per_s)
print("Longitude(grad): ", longitude)
print("Latitude(grad): ", latitude)


LK = wgs84.latlon(latitude * N, longitude * W, sea_hight)
ICRS_LK = LK.at(ts.now())
print(ICRS_LK)
print('Position components:', ICRS_LK.position.km)


dist = (geocentre - ICRS_LK).distance().km
print('NOAA2 & LK distance:', dist)
difference = satellite - LK   
topocentric = difference.at(t) 
print(topocentric.distance().km)
alt, az, distance = topocentric.altaz()
if alt.degrees > 0:
    print('The ISS is above the horizon')

print('Altitude:', alt)
print('Azimuth:', az)
print('Distance: {:.1f} km'.format(distance.km))

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
z = np.linspace(-2, 2, 100)
r = z**2 + 1
x = r * np.sin(theta)
y = r * np.cos(theta)
ax.plot(x, y, z, label='parametric curve')
ax.legend()
plt.savefig("Satellite appearance.png")
plt.show()





import matplotlib.pyplot as plt
import numpy as np
# import seaborn as sns

s = 12

L = 300
sz = 0.5*L
DATA_DIR = 'Data/'
IMAGE_DIR = 'IMG/'

#particle plot
i, x, y = np.loadtxt(DATA_DIR + 'clusterData.csv', unpack = True, delimiter = ',')
r, n = np.loadtxt(DATA_DIR + 'radialData.csv', unpack=True, delimiter = ',')
dt_f, clusterSize_f = np.loadtxt(DATA_DIR + 'time_to_add_fixedspawn.csv', unpack=True, delimiter = ',')
dt_m, clusterSize_m = np.loadtxt(DATA_DIR + 'time_to_add_movingspawn.csv', unpack=True, delimiter = ',')
dt_b, clusterSize_b = np.loadtxt(DATA_DIR + 'time_to_add_addedbias.csv', unpack=True, delimiter = ',')

plt.figure()
plt.scatter(x, y, s=2)
plt.scatter(0, 0, s=2, c='r')
plt.tick_params(direction = 'in', size = 8, top = True, right = True, labelsize=s-2)
plt.xlim(-sz, sz)
plt.ylim(-sz, sz)
plt.savefig(IMAGE_DIR + "dla.png", dpi=300, bbox_inches='tight')

plt.figure()
#fit = np.polyfit(np.log(r[0:12]), np.log(n[0:12]), 1)
fit = np.polyfit(np.log(r), np.log(n), 1)
fit = np.poly1d(fit)
print(fit)
x = np.linspace(2, np.log(r[-1]), 10)
y = fit(x)
plt.plot(np.log(r), np.log(n), 'bo', markersize=3)
plt.plot(x, y, 'k--')
plt.tick_params(direction = 'in', size = 8, top = True, right = True, labelsize=s-2)
#plt.xlim(2, np.log(r[-1])+0.5)
plt.xlabel("log(r)")
plt.ylabel("log(N(r))")
plt.savefig(IMAGE_DIR + "radDensity.png", dpi=300, bbox_inches='tight')

plt.figure()
plt.plot(dt_f, clusterSize_f, 'r-o', label='Fixed Spawn', markersize=2)
print(f"{len(dt_f)-1} million cycles")
plt.plot(dt_m, clusterSize_m, 'b-o', label='Moving Spawn', markersize=2)
print(f"{len(dt_m)-1} million cycles")
plt.plot(dt_b, clusterSize_b, 'g-o', label='Moving Spawn, Added Bias', markersize=2)
print(f"{len(dt_b)-1} million cycles")
plt.xlabel("time (s)")
plt.ylabel("Cluster Size")
plt.legend(loc='best')
plt.savefig(IMAGE_DIR + "time_to_add.png", dpi=300, bbox_inches='tight')

import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

s = 12

L = 300
sz = 0.5*L
DATA_DIR = 'Data/'
IMAGE_DIR = 'IMG/'

#particle plot
i, x, y = np.loadtxt(DATA_DIR + 'clusterData.csv', unpack = True, delimiter = ',')

plt.figure()
plt.scatter(x, y, s=3)
plt.tick_params(direction = 'in', size = 8, top = True, right = True, labelsize=s-2)
plt.xlim(-sz, sz)
plt.ylim(-sz, sz)
plt.savefig(IMAGE_DIR + "dla.png", dpi=300, bbox_inches='tight')


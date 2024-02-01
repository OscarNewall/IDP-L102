import numpy as np
import matplotlib.pyplot as plt

data = np.load("software/imu_dump/A_6_66K.npy")

plt.plot(data[:,0])
plt.show()
from matplotlib import pyplot as plt
import pandas as pd
import numpy as np
import sys

plot_step = 2000
max_step = 20000
dt = 0.000001


names = np.append(1, np.arange(plot_step,max_step,plot_step))
rhos = []

for name in names:
    rhos.append(pd.read_csv("./PIC" + str(name) + ".csv",header=None).values.astype(float))

xs = np.linspace(0, 1, len(rhos[0]))

fig, ax = plt.subplots(len(names), sharex='col', sharey='row')


for i in range(len(names)):
    ax[i].plot(xs, rhos[i])
    ax[i].set_ylabel("t = {:.3f}".format(dt * names[i]))

plt.show()
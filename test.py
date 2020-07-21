from roboticstoolbox import mstraj
import numpy as np
import rospy
import pdb

path = np.array([
        [2173, 2526, 1412, 2502],
        [2105,  1320, 1408, 2703],
        [2070, 1539, 2394, 2194],
        [2578, 2394, 2368, 2194]
        ])

out = mstraj(path, dt=0.1, tacc=1, tsegment=[2, 2, 2])
print(out.q)
import matplotlib.pyplot as plt
plt.figure()
plt.plot(out.t, out.q)
plt.grid(True)
plt.xlabel('time')
plt.legend(('$q_0$', '$q_1$'))
plt.plot(out.arrive, out.via, 'bo')

plt.figure()
plt.plot(out.q[:,0], out.q[:,1])
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.show()

# pdb.set_trace()

from pyscurve import ScurvePlanner, plot_trajectory
import numpy as np
from pyscurve.trajectory import get_trajectory_data
import matplotlib.pyplot as plt

if __name__ == "__main__":
    def createMotorPath(start, end):
        p = ScurvePlanner()

        q0 = [start]
        q1 = [end]
        v0 = [0.]
        v1 = [.1]
        v_max = 20.
        a_max = 30.
        j_max = 100.
        T = 2

        tr = p.plan_trajectory(q0, q1, v0, v1, v_max, a_max, j_max, t=T)
        return get_trajectory_data(tr, 0.1)

    q0Path = createMotorPath(2.8684, -1.0927)
    q1Path = createMotorPath(0.6837, 1.0457)
    q2Path = createMotorPath(-0.4663, -0.4665)
    q3Path = createMotorPath(1.1663, 0.6033)

    newdata = np.squeeze(q0Path[0])  # Shape is now: (10, 80)
    plt.plot(newdata)  # plotting by columns
    plt.show()

    newdata = np.squeeze(q0Path[1])  # Shape is now: (10, 80)
    plt.plot(newdata)  # plotting by columns
    plt.show()

    newdata = np.squeeze(q0Path[2])  # Shape is now: (10, 80)
    plt.plot(newdata)  # plotting by columns
    plt.show()

    print("yeet")

'''from pyscurve import ScurvePlanner, plot_trajectory

if __name__ == "__main__":
    p = ScurvePlanner()
    q0 = [2.8684, 0.6837, -0.4663, 1.1663]
    q1 = [-1.0927, 1.0457, -0.4663, 0.6033]
    v0 = [0., 1., 0., 0.2]
    v1 = [.1, 0.0, 0.2, 0.3]
    v_max = 30.
    a_max = 30.
    j_max = 100.
    T = 3.0

    tr = p.plan_trajectory(q0, q1, v0, v1, v_max, a_max, j_max, t=T)
    plot_trajectory(tr, dt=0.01)
'''

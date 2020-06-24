import robopy.base.model as model
import numpy as np
from robopy import *
import robopy.base.pose as pose



def main():
    '''robot = model.Scarab()

    a = np.transpose(np.asmatrix(np.linspace(1, -180, 500)))
    b = np.transpose(np.asmatrix(np.linspace(1, 180, 500)))
    c = np.transpose(np.asmatrix(np.linspace(1, 90, 500)))
    d = np.transpose(np.asmatrix(np.linspace(1, 450, 500)))
    e = np.asmatrix(np.zeros((500, 1)))
    f = np.concatenate((d, b, a, e, c, d), axis=1)

    robot.animate(stances=f, frame_rate=30, unit='deg')'''
    '''
    links = [Revolute(d=0.15, a=0.6, alpha=pi / 2, j=0, theta=0, offset=0, qlim=(-30 * pi / 180, 30 * pi / 180)),
             Revolute(d=0, a=0.85, alpha=0, j=0, theta=0, offset=0, qlim=(-40 * pi / 180, 40 * pi / 180)),
             Revolute(d=0, a=0.95, alpha=0, j=0, theta=0, offset=0, qlim=(-40 * pi / 180, 40 * pi / 180)),
             Revolute(d=0, a=0.8, alpha=-pi / 2, j=0, theta=0, offset=0, qlim=(-50 * pi / 180, 50 * pi / 180))]
    scarab = SerialLink(links=links)''' #transl = translation(x,y,z)
    q1 = 0
    q2 = 0.5008
    q3 = 0.5919
    q4 = 0.8347

    start = [0.3, 0.3, 0.3, 0.3]
    end = [-0.3, -0.3, -0.3, -0.3]



    c = pose.transforms.trotz(q1)*pose.transforms.transl(0, 0, 0.15)*pose.transforms.transl(0.6, 0, 0)*\
        pose.transforms.trotx(pi/2)*pose.transforms.trotz(q2)*pose.transforms.transl(0.85, 0, 0)*pose.transforms.trotz(q3)*\
        pose.transforms.transl(0.95, 0, 0)*pose.transforms.trotz(q4)*pose.transforms.transl(0.8, 0, 0)*pose.transforms.trotx(-pi/2)
    #*pose.transforms.troty(0.7)

    print(c)





if __name__ == '__main__':
    main()
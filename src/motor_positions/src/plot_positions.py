from robopy import SerialLink, Revolute
from robopy import transforms as tr
from robopy import graphics
from math import pi
import numpy as np
import robopy.base.model as model
from robopy import ishomog
import pdb

d2r = pi / 180


class Scarab(SerialLink):
    def __init__(self, base=None):
        self.scale = 1

        self.qz = np.matrix([0, 0])

        links = [Revolute(d=0.15, a=0.6, j=0, alpha=pi / 2, theta=0, offset=0, qlim=(-30 * d2r, 30 * d2r)),
                      Revolute(d=0, a=0.85, j=0, alpha=pi / 2, theta=0, offset=0, qlim=(-40 * d2r, 40 * d2r))]

        if base is None:
            base = tr.trotx(-90, unit="deg")
        else:
            assert ishomog(base, (4, 4))

        file_names = SerialLink._setup_file_names(3)
        # pdb.set_trace()
        colors = graphics.vtk_named_colors(["DimGray", "IndianRed", "IndianRed"])

        super().__init__(links=links, base=base, name='orion5', stl_files=file_names, colors=colors)


robot = Scarab()
# robot = model.Orion5()

# qn = np.matrix([0, 0, 0, 0, 0, 0])


qn = np.matrix([0, 0])
robot.plot(qn)

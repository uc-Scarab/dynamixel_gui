"""
Defines the object 'arm' in the current workspace

Also define the vector qz = [pi/4,0,-pi/3]
"""

from roboticstoolbox.robot.serial_link import *

L = []

L.append(Link('a', 0.1, 'd', 1, 'alpha', pi/2, 'type', 'revolute'))
L.append(Link('a', 1, 'type', 'revolute'))
L.append(Link('a', 0.5, 'type', 'revolute'))


qz = [pi/4,0,-pi/3]

arm = SerialLink(L, name='Upright Arm')


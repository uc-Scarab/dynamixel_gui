# -*- coding: utf-8 -*-
from __future__ import print_function
import argparse
import os
import stat
import sys

# find the import for catkin's python package - either from source space or from an installed underlay
if os.path.exists(os.path.join('/home/charles/catkin_ws/install_isolated/share/catkin/cmake', 'catkinConfig.cmake.in')):
    sys.path.insert(0, os.path.join('/home/charles/catkin_ws/install_isolated/share/catkin/cmake', '..', 'python'))
try:
    from catkin.environment_cache import generate_environment_script
except ImportError:
    # search for catkin package in all workspaces and prepend to path
    for workspace in "/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/rosserial_embeddedlinux;/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/rosserial_client;/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/rosserial_msgs;/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/rosserial_mbed;/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/rosserial_chibios;/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/rosserial_arduino;/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/rosserial;/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/motor_positions;/home/charles/devel/ros/scarab/scarab_ros/devel;/home/charles/catkin_ws/install_isolated".split(';'):
        python_path = os.path.join(workspace, 'lib/python2.7/dist-packages')
        if os.path.isdir(os.path.join(python_path, 'catkin')):
            sys.path.insert(0, python_path)
            break
    from catkin.environment_cache import generate_environment_script

code = generate_environment_script('/home/charles/devel/ros/scarab/scarab_ros/devel_isolated/rosserial_python/env.sh')

output_filename = '/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_python/catkin_generated/setup_cached.sh'
with open(output_filename, 'w') as f:
    #print('Generate script for cached setup "%s"' % output_filename)
    f.write('\n'.join(code))

mode = os.stat(output_filename).st_mode
os.chmod(output_filename, mode | stat.S_IXUSR)

catkin_make -DCMAKE_BUILD_TYPE=Debug
source devel/setup.zsh
rosrun motor_positions publish_positions
#gdb devel/lib/motor_positions/publish_positions

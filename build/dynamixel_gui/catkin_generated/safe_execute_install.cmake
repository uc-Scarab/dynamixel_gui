execute_process(COMMAND "/home/charles/devel/ros/dynamixel_gui/build/dynamixel_gui/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/charles/devel/ros/dynamixel_gui/build/dynamixel_gui/catkin_generated/python_distutils_install.sh) returned error code ")
endif()

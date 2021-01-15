#!/bin/bash
sudo su
cd /home/fshs/catkin_ws/
source /home/fshs/catkin_ws/devel/setup.bash
rosrun daq_ros_driver daq_ros_driver
wait
exit 0




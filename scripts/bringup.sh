roslaunch hsr_bringup co605_gripper_go.launch &
#roslaunch hsr_bringup co605_go.launch &

for((i=0; i<5; i++))
  do
    sleep 1;
    var=$(ps -le |grep rviz |awk '{print $4}')
    echo " co605_gripper_go 测试 " $var
    if [ -n  $var ];then
      echo " co605_gripper_go ok? " $var
      sleep 2
      break;
    fi
done;
sleep 5
roslaunch realsense2_camera rs_camera.launch &
roslaunch hsr_bringup publish_d435i_calibration_co605_gripper.launch &
roslaunch vision_bridge vision_bridge_yolo6d-realsense2.launch &

roslaunch gripper_bridge gripper_bridge.launch &
rosrun perception_bridge perception_bridge &
sleep 5
gnome-terminal -x bash -c "roslaunch kinect2_bridge kinect2_bridge.launch " &
roslaunch hsr_bringup publish_kinect_calibration_.launch &
rosrun dm_bridge dm_bridge &
#gnome-terminal -x bash -c "rosrun hsr_robot_voice pick_assistant" &
rosrun planner_bridge planner >/home/fshs/catkin_ws/log/planner.log 2>&1 &
rosrun motion_bridge motion_bridge_exe >/home/fshs/catkin_ws/log/motion_bridge_exe.log 2>&1 &
roslaunch  pickplace_bridge robotIO_pickplace_bridge.launch &
#gnome-terminal -x bash -c "roslaunch pickplace_bridge serial_pickplace_bridge.launch " &
#rosrun hscfsm_bridge hscfsm_bridge >/home/fshs/catkin_ws/log/hscfsm_bridge.log 2>&1 &
gnome-terminal -x bash -c "rosrun hscfsm_bridge hscfsm_bridge " &
rosrun gripperquickchange_bridge gripperquickchange_bridge &
rosservice call /set_robot_enable "enable: false"
sleep 3
gnome-terminal -x bash -c "roslaunch force_bridge bring_up_realRobot.launch " &
sleep 1
rosrun force_bridge motionCoorControl >/home/fshs/catkin_ws/log/motionCoorControl.log 2>&1 &
sleep 1
rosrun force_bridge shakeHandJudge &
sleep 1
gnome-terminal -x bash -c "rosrun trajectory_repetition trajectory_repetition_node " &
#rosrun trajectory_repetition trajectory_repetition_node >/home/fshs/catkin_ws/log/trajectory_repetition_node.log 2>&1 &
sleep 1
#rosrun hs_multigripper forceSensor_run.sh &
rosrun daq_ros_driver daq_ros_driver &
sleep 5
#rosservice call /setGripper "gripperName: 'SerialGripper'"
#rosservice call /connectGripper "{}"
rosrun perception_bridge quickChangeScene.sh

#gnome-terminal -x bash -c "rosrun asr_bridge asr_bridge" &

rosrun hscloudcollection_bridge hscloudcollection_bridge_node  >/home/fshs/catkin_ws/log/hscloudcollection_bridge_node.log 2>&1 &
sleep 2
rosservice call /connectCloudSer "{}"

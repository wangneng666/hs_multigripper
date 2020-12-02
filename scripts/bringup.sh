roslaunch hsr_bringup co605_gripper_go.launch &

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


roslaunch gripper_bridge gripper_bridge.launch &
rosrun perception_bridge perception_bridge &
sleep 5
roslaunch kinect2_bridge kinect2_bridge.launch & 
roslaunch hsr_bringup publish_kinect_calibration_.launch &
roslaunch realsense2_camera rs_camera.launch &
roslaunch hsr_bringup publish_d435i_calibration_co605_gripper.launch &
roslaunch vision_bridge vision_bridge_yolo6d-realsense2.launch &
rosrun dm_bridge dm_bridge &
#gnome-terminal -x bash -c "rosrun hsr_robot_voice pick_assistant" &
gnome-terminal -x bash -c "rosrun planner_bridge planner" &
rosrun motion_bridge motion_bridge_exe &
gnome-terminal -x bash -c "roslaunch pickplace_bridge serial_pickplace_bridge.launch " &
gnome-terminal -x bash -c "rosrun hscfsm_bridge hscfsm_bridge " & 

#sleep 10
#rosservice call /setGripper "gripperName: 'SerialGripper'"
#rosservice call /connectGripper "{}"
#rosrun perception_bridge shelf.sh

#cd ~/catkin_ws_v3/kdxf/Linux_aiui5.5.1059.0000_5d706e05/samples/aiui_sample/build/
#gnome-terminal -x bash -c "rosrun asr_bridge asr_bridge" &
#rosrun hsr_robot_voice voice_assistant &

#kill $(ps -ef | grep kinect2 | awk '{print $2}')

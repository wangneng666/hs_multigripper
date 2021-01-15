#!/bin/bash
#去到科大迅飞库的路径下
cd ~/catkin_ws/kdxf/Linux_aiui5.5.1059.0000_5d706e05/samples/aiui_sample/build
source ~/.bashrc
#启动麦克风监听
rosrun asr_bridge asr_bridge >/home/fshs/catkin_ws/log/asr_bridge.log 2>&1 &

#启动语音智能助手
rosrun hsr_robot_voice voice_assistant &
#启动语音智能助手
rosrun hs_multigripper VoiceControl &
wait
exit 0

#!/bin/bash
#去到科大迅飞库的路径下
rosnode kill /asr_bridge
rosnode kill /Voice_assistant
rosnode kill /userIntentSolve
wait
exit 0




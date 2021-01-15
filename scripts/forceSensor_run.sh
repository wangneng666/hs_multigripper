#!/bin/bash

sudo -S sh /home/fshs/catkin_ws/src/hs_multigripper/scripts/forceSensor.sh << EOF
0
EOF

wait
exit 0




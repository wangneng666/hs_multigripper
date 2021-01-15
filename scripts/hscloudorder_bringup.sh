#!/bin/bash
rosrun hscloudorder_bridge hscloudorder_bridge_node  &
sleep 2
rosservice call /connectCloud "{}"
exit 0




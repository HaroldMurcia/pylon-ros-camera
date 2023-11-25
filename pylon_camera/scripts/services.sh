#!/bin/bash

echo "Pylon services"
sleep 3
# ## TRIGGER
#     https://docs.baslerweb.com/triggered-image-acquisition
#     set_trigger_activation: 1 #rise pulse
#     set_trigger_source: 2     # line 3
#     set_trigger_selector: 0   # 0 = Frame start, 1 = Frame burst start 
#     set_trigger_mode: 0       #0=normal, 1==fast 
# 

rosservice call /pylon_camera_node/set_trigger_selector 0    # 0 = Frame start, 1 = Frame burst start 
rosservice call /pylon_camera_node/set_trigger_activation 1  #rise pulse
rosservice call /pylon_camera_node/set_trigger_mode true
rosservice call /pylon_camera_node/set_trigger_source 2      # line 3
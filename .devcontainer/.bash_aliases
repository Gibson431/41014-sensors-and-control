alias sb="source ~/.bash_aliases"
alias cw="cd ~/catkin_ws"

sr () {
    source "/opt/ros/${ROS_DISTRO}/setup.bash"
    source "${HOME}/catkin_ws/devel/setup.bash"
};

cm  () {
    cw
    catkin_make -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    sr
};

cm
sr

export TURTLEBOT3_MODEL=waffle_pi
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:$HOME/catkin_ws/src/sensors-and-control/models
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:$HOME/catkin_ws/src/turtlebot3_simulations/turtlebot3_gazebo/models
export GAZEBO_RESOURCE_PATH=$GAZEBO_RESOURCE_PATH:$HOME/catkin_ws/src/sensors-and-control
export GAZEBO_PLUGIN_PATH=$GAZEBO_PLUGIN_PATH:$HOME/catkin_ws/devel
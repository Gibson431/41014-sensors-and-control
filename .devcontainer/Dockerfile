FROM osrf/ros:noetic-desktop-full

# Add vscode user with same UID and GID as your host system
# (copied from https://code.visualstudio.com/remote/advancedcontainers/add-nonroot-user#_creating-a-nonroot-user)
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
# Switch from root to user
USER $USERNAME

# Add user to video group to allow access to webcam
RUN sudo usermod --append --groups video $USERNAME

# Update all packages
RUN sudo apt update && sudo apt upgrade -y

# Install Git
RUN sudo apt install -y git

# Customise the installation
USER root

RUN apt-get update -y && apt-get install -y \
    python3 \
    python3-yaml \
    python3-rospkg

RUN apt-get update -y && apt-get install -y \
    ros-noetic-navigation \
    ros-noetic-slam-toolbox \
    ros-noetic-slam-gmapping 

RUN apt-get update -y && apt-get install -y \
    ros-noetic-robot-controllers \
    ros-noetic-moveit-core \
    ros-noetic-teleop-twist-keyboard \
    ros-noetic-topic-tools

RUN apt-get update -y && apt-get install -y \
    ros-noetic-turtlebot3 \
    ros-noetic-turtlebot3-gazebo 

RUN apt-get update -y && apt-get install -y \
    ros-noetic-fetch-navigation
    
RUN apt-get update && apt-get install -y \
    python3-pip

RUN apt-get update && apt-get install -y \
    ros-noetic-rgbd-launch

RUN ln -s /usr/bin/python3 /usr/bin/python

USER $USERNAME

RUN pip install defusedxml

# Rosdep update
RUN rosdep update

RUN mkdir -p /home/$USERNAME/catkin_ws/src

RUN git clone https://github.com/pal-robotics/gazebo_ros_link_attacher.git /home/$USERNAME/catkin_ws/src/gazebo_ros_link_attacher

RUN git clone https://github.com/pal-robotics/aruco_ros.git /home/$USERNAME/catkin_ws/src/aruco_ros/

RUN git clone https://github.com/ZebraDevs/fetch_ros.git /home/$USERNAME/catkin_ws/src/fetch_ros/ \
    && rm -rf /home/$USERNAME/catkin_ws/src/fetch_ros/fetch_depth_layer
# fetch_depth_layer doesn't compile on noetic

RUN git clone https://github.com/ZebraDevs/fetch_gazebo.git /home/$USERNAME/catkin_ws/src/fetch_gazebo \
    && cd /home/$USERNAME/catkin_ws/src/fetch_gazebo \
    && git checkout gazebo11


# Source the ROS setup file
RUN echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> ~/.bashrc

# RUN cd /home/$USERNAME/catkin_ws && /opt/ros/noetic/bin/catkin_make 
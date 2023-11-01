# 41014-sensors-and-control

## Collaborators

Timothy Gibson, Ruby Kasif, Anthony Chalhoub

## Installation

### Requirements

- [Fetch Robot System](https://fetchrobotics.com/)
    - [fetch_ros](https://github.com/ZebraDevs/fetch_ros)
    - [fetch_gazebo](https://github.com/ZebraDevs/fetch_gazebo.git)
- [Turtlebot 3](https://emanual.robotis.com/docs/en/platform/turtlebot3/overview/)
    - [turtlebot3](https://github.com/ROBOTIS-GIT/turtlebot3)
    - [turtlebot3_simulations](https://github.com/ROBOTIS-GIT/turtlebot3_simulations)
- [Aruco](https://docs.opencv.org/4.x/d5/dae/tutorial_aruco_detection.html)
    - [aruco_ros](https://github.com/pal-robotics/aruco_ros)
- Link Attacher
    - [gazebo_ros_link_attacher](https://github.com/pal-robotics/gazebo_ros_link_attacher)

## Usage

`simulation.launch` - creates an empty gazebo world with the fetch robot and a turtlebot3 with an aruco fiducial mounted above it

`follow.launch` - starts the aruco tracking node and the navigation nodes for both guide and follower

`guide_teleop.launch` - initiates a teleop controller for the 'guide' (turtlebot3)

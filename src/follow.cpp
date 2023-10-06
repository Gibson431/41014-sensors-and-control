#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>

class FetchFollower {
public:
  FetchFollower() {
    // Initialize ROS node handle and subscribers
    nh_.reset(new ros::NodeHandle());

    // Set callback for when marker is recieved
    marker_sub_ =
        nh_->subscribe("/marker_pose", 1, &FetchFollower::markerCallback, this);

    // Initialize the publisher for robot movement
    marker_pub_ = nh_->advertise<geometry_msgs::PoseStamped>("/waypoint", 1);
    
  }

  void markerCallback(const geometry_msgs::PoseStamped::ConstPtr &pose) {
    marker_pub_.publish(*pose);
  }

private:
  ros::NodeHandlePtr nh_;
  ros::Subscriber marker_sub_;
  ros::Publisher marker_pub_;
};


int main(int argc, char **argv) {
  ros::init(argc, argv, "fetch_follower_node");
  FetchFollower fetch_follower;

  ros::spin();

  return 0;
}
